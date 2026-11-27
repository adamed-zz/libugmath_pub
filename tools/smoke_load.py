import argparse
import ctypes
import json
import math
import os
import struct
import sys
from ctypes import wintypes

CINT = ctypes.c_int
CDBL = ctypes.c_double
CBOOL = ctypes.c_bool
PD = ctypes.POINTER(ctypes.c_double)
PPD = ctypes.POINTER(ctypes.POINTER(ctypes.c_double))


class V3(ctypes.Structure):
    _fields_ = [('x', ctypes.c_double), ('y', ctypes.c_double),
                ('z', ctypes.c_double)]


class P3(ctypes.Structure):
    _fields_ = [('x', ctypes.c_double), ('y', ctypes.c_double),
                ('z', ctypes.c_double)]


class M3(ctypes.Structure):
    _fields_ = [('m', ctypes.c_double * 9)]


class M4(ctypes.Structure):
    _fields_ = [('m', ctypes.c_double * 16)]


PV3 = ctypes.POINTER(V3)
PM3 = ctypes.POINTER(M3)
PM4 = ctypes.POINTER(M4)
PP3 = ctypes.POINTER(P3)

IDENT3 = [1, 0, 0, 0, 1, 0, 0, 0, 1]
IDENT4 = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1]


def V(x, y, z):
    return V3(x, y, z)


def P(x, y, z):
    return P3(x, y, z)


def M(values):
    out = M3()
    for i, v in enumerate(values):
        out.m[i] = v
    return out


def M4v(values):
    out = M4()
    for i, v in enumerate(values):
        out.m[i] = v
    return out


def near(a, b, tol=1e-9):
    return abs(a - b) <= tol


def mat_near(vals, exp, tol=1e-9):
    return all(near(a, b, tol) for a, b in zip(vals, exp))


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument('--dll', required=True)
    ap.add_argument('--nxbin', required=True,
                    help='NX NXBIN directory containing libsyss.dll')
    ap.add_argument('--json')
    ap.add_argument('--quiet', action='store_true')
    args = ap.parse_args(argv)
    k32 = ctypes.WinDLL('kernel32', use_last_error=True)
    k32.SetDllDirectoryW.argtypes = [wintypes.LPCWSTR]
    k32.SetDllDirectoryW.restype = wintypes.BOOL
    k32.LoadLibraryW.argtypes = [wintypes.LPCWSTR]
    k32.LoadLibraryW.restype = wintypes.HMODULE
    k32.GetProcAddress.argtypes = [wintypes.HMODULE, wintypes.LPCSTR]
    k32.GetProcAddress.restype = ctypes.c_void_p
    k32.GetModuleFileNameW.argtypes = [wintypes.HMODULE, wintypes.LPWSTR,
                                      wintypes.DWORD]
    k32.GetModuleFileNameW.restype = wintypes.DWORD
    k32.GetModuleHandleW.argtypes = [wintypes.LPCWSTR]
    k32.GetModuleHandleW.restype = wintypes.HMODULE
    k32.GetModuleHandleExW.argtypes = [wintypes.DWORD, ctypes.c_void_p,
                                      ctypes.POINTER(wintypes.HMODULE)]
    k32.GetModuleHandleExW.restype = wintypes.BOOL
    flag_from_addr = 4
    flag_unchanged = 2
    nxbin = os.path.abspath(args.nxbin)
    dll = os.path.abspath(args.dll)
    report = {'tool': 'smoke_load.py', 'dll': dll, 'nxbin': nxbin,
              'setdll_rc': None, 'load_rc': None, 'load_error': None,
              'libsyss_path': None, 'module_path': None,
              'tests': [], 'data_exports': []}

    def mod_path(hm):
        if not hm:
            return None
        buf = ctypes.create_unicode_buffer(32768)
        n = k32.GetModuleFileNameW(hm, buf, 32768)
        return buf.value if n else None

    def in_module(addr):
        if not addr:
            return False
        hm2 = wintypes.HMODULE()
        ok = k32.GetModuleHandleExW(flag_from_addr | flag_unchanged,
                                    ctypes.c_void_p(addr), ctypes.byref(hm2))
        return bool(ok) and hm2.value == int(hm)

    rc = k32.SetDllDirectoryW(nxbin)
    report['setdll_rc'] = bool(rc)
    for dep in ('msvcp140.dll', 'vcruntime140.dll', 'vcruntime140_1.dll'):
        p = os.path.join(nxbin, dep)
        if os.path.isfile(p):
            k32.LoadLibraryW(p)
    hm = k32.LoadLibraryW(dll)
    report['load_error'] = ctypes.get_last_error()
    report['load_rc'] = bool(hm)
    report['module_path'] = mod_path(hm) if hm else None
    libsyss = k32.GetModuleHandleW('libsyss.dll')
    report['libsyss_path'] = mod_path(libsyss) if libsyss else None
    if not hm:
        print('LOAD FAILED err=%d (check --nxbin contains libsyss.dll)'
              % report['load_error'])
        if args.json:
            with open(args.json, 'w', encoding='utf-8') as f:
                json.dump(report, f, ensure_ascii=False, indent=1)
        return 2
    p0 = k32.GetProcAddress(hm, b'?merrorlevel@@YAHXZ')
    hm2 = wintypes.HMODULE()
    k32.GetModuleHandleExW(flag_from_addr | flag_unchanged,
                           ctypes.c_void_p(p0), ctypes.byref(hm2))
    report['module_base'] = hex(hm2.value) if hm2.value else None

    def getp(name):
        return k32.GetProcAddress(hm, name.encode())

    def call(name, restype, argtypes, *fargs, category=''):
        addr = getp(name)
        if not addr:
            add(name, category, '', None, 'FAIL', 'GetProcAddress NULL')
            return None
        try:
            fn = ctypes.WINFUNCTYPE(restype, *argtypes)(addr)
            return fn(*fargs)
        except Exception as e:
            add(name, category, '', None, 'FAIL', 'call exception: %r' % (e,))
            return None

    def add(name, category, call_desc, result, verdict, detail=''):
        report['tests'].append({'name': name, 'category': category,
                                'call': call_desc, 'result': result,
                                'verdict': verdict, 'detail': detail})

    DATA_EXPORTS = [
        ('?acom@@3Uacom_s@@A', 4240),
        ('?delaunay_vtable@@3Udelaunay_vtable_s@@A', 868),
        ('?gbspline_vtable@@3Ugbspline_vtable_t@@A', 112),
        ('?spint@@3Uspint_s@@A', 304),
    ]
    for name, size in DATA_EXPORTS:
        addr = getp(name)
        entry = {'name': name, 'addr': hex(addr) if addr else None,
                 'in_module': in_module(addr) if addr else False,
                 'size_evidence': size}
        if addr:
            try:
                blob = ctypes.string_at(addr, min(size, 64))
                entry['readable'] = True
                entry['first_bytes_hex'] = blob[:16].hex()
            except Exception as e:
                entry['readable'] = False
                entry['error'] = repr(e)
        else:
            entry['readable'] = False
            entry['error'] = 'GetProcAddress NULL'
        report['data_exports'].append(entry)
        ok = entry.get('readable') and entry.get('in_module')
        add(name, 'data', 'GetProcAddress + read %d bytes' % min(size, 64),
            entry.get('first_bytes_hex'), 'PASS' if ok else 'FAIL',
            'size=%d in_module=%s' % (size, entry.get('in_module')))

    A2 = (ctypes.c_double * 4)(2.0, 1.0, 1.0, 3.0)
    b2 = (ctypes.c_double * 2)(5.0, 8.0)
    x2 = (ctypes.c_double * 2)(-9.0, -9.0)
    r = call('?SOLVE_solve_2equations@@YAHQEAY01NQEAN1@Z', CINT, [PD, PD, PD],
              A2, b2, x2, category='SOLVE')
    if r is not None:
        ok = r == 0 and near(x2[0], 1.4) and near(x2[1], 2.2)
        add('?SOLVE_solve_2equations@@YAHQEAY01NQEAN1@Z', 'SOLVE', '2x2',
            {'rc': r, 'x': [x2[0], x2[1]]}, 'PASS' if ok else 'FAIL',
            'expect rc=0 x={1.4,2.2}')

    A3 = (ctypes.c_double * 9)(1, 0, 0, 0, 1, 0, 0, 0, 1)
    b3 = (ctypes.c_double * 3)(1.0, 2.0, 3.0)
    x3 = (ctypes.c_double * 3)(-9.0, -9.0, -9.0)
    r = call('?SOLVE_solve_3equations@@YAHQEAY02NQEAN1@Z', CINT, [PD, PD, PD],
              A3, b3, x3, category='SOLVE')
    if r is not None:
        ok = r == 0 and near(x3[0], 1.0) and near(x3[1], 2.0) and near(x3[2], 3.0)
        add('?SOLVE_solve_3equations@@YAHQEAY02NQEAN1@Z', 'SOLVE', '3x3',
            {'rc': r, 'x': list(x3)}, 'PASS' if ok else 'FAIL',
            'expect rc=0 x={1,2,3}')

    coefq = (ctypes.c_double * 3)(-1.0, 0.0, 1.0)
    rootsq = (ctypes.c_double * 2)(-9.0, -9.0)
    r = call('?SOLVE_quadratic@@YAHQEBNQEAN@Z', CINT, [PD, PD], coefq, rootsq,
              category='SOLVE')
    if r is not None:
        got = sorted([rootsq[0], rootsq[1]]) if r == 2 else [rootsq[0]]
        ok = r == 2 and near(got[0], -1.0) and near(got[1], 1.0)
        add('?SOLVE_quadratic@@YAHQEBNQEAN@Z', 'SOLVE', 'x^2-1=0',
            {'rc': r, 'roots': got}, 'PASS' if ok else 'FAIL',
            'expect rc=2 roots={-1,1}')

    coefc = (ctypes.c_double * 4)(-1.0, 0.0, 0.0, 1.0)
    rootsc = (ctypes.c_double * 3)(-9.0, -9.0, -9.0)
    r = call('?SOLVE_cubic@@YAHQEBNQEAN@Z', CINT, [PD, PD], coefc, rootsc,
              category='SOLVE')
    if r is not None:
        ok = r == 1 and near(rootsc[0], 1.0)
        add('?SOLVE_cubic@@YAHQEBNQEAN@Z', 'SOLVE', 'x^3-1=0',
            {'rc': r, 'root0': rootsc[0]}, 'PASS' if ok else 'FAIL',
            'expect rc=1 root=1')

    def lu_case(name, with_abort):
        row0 = (ctypes.c_double * 2)(2.0, 1.0)
        row1 = (ctypes.c_double * 2)(1.0, 3.0)
        amat = (ctypes.POINTER(ctypes.c_double) * 2)(
            ctypes.cast(row0, ctypes.POINTER(ctypes.c_double)),
            ctypes.cast(row1, ctypes.POINTER(ctypes.c_double)))
        col0 = (ctypes.c_double * 1)(5.0)
        col1 = (ctypes.c_double * 1)(8.0)
        bmat = (ctypes.POINTER(ctypes.c_double) * 2)(
            ctypes.cast(col0, ctypes.POINTER(ctypes.c_double)),
            ctypes.cast(col1, ctypes.POINTER(ctypes.c_double)))
        if with_abort:
            r = call(name, CINT, [PPD, PPD, CINT, CINT, ctypes.c_void_p],
                      amat, bmat, 2, 1, None, category='SOLVE')
        else:
            r = call(name, CINT, [PPD, PPD, CINT, CINT],
                      amat, bmat, 2, 1, category='SOLVE')
        if r is not None:
            ok = r == 0 and near(col0[0], 1.4) and near(col1[0], 2.2)
            add(name, 'SOLVE', 'LU 2x2',
                {'rc': r, 'B': [col0[0], col1[0]]}, 'PASS' if ok else 'FAIL',
                'expect rc=0 B={1.4,2.2}')

    lu_case('?SOLVE_lu_solver@@YAHPEAPEAN0HH@Z', False)
    lu_case('?SOLVE_lu_solver_with_abort@@YAHPEAPEAN0HHP6A_NXZ@Z', True)

    row0 = (ctypes.c_double * 2)(2.0, 1.0)
    row1 = (ctypes.c_double * 2)(1.0, 3.0)
    amat = (ctypes.POINTER(ctypes.c_double) * 2)(
        ctypes.cast(row0, ctypes.POINTER(ctypes.c_double)),
        ctypes.cast(row1, ctypes.POINTER(ctypes.c_double)))
    indx = (ctypes.c_int * 2)(-1, -1)
    dval = ctypes.c_double(0.0)
    r = call('?ludcmp_a_with_abort@@YAHPEAPEANHPEAHPEANP6A_NXZ@Z', CINT,
              [PPD, CINT, ctypes.POINTER(ctypes.c_int), PD, ctypes.c_void_p],
              amat, 2, indx, ctypes.byref(dval), None, category='SOLVE')
    if r is not None:
        add('?ludcmp_a_with_abort@@YAHPEAPEANHPEAHPEANP6A_NXZ@Z', 'SOLVE',
            'ludcmp 2x2', {'rc': r, 'indx': [indx[0], indx[1]], 'd': dval.value},
            'PASS' if r == 0 else 'FAIL', 'expect rc=0')

    def mtx3_case(name, fargs, argtypes, check):
        out = M3()
        r = call(name, CINT, argtypes, *(fargs + (ctypes.byref(out),)),
                 category='MTX')
        if r is not None:
            vals = list(out.m)
            ok, note = check(r, vals)
            add(name, 'MTX', '', {'rc': r, 'out': vals},
                'PASS' if ok else 'FAIL', note)

    mtx3_case('?MTX3_init@@YAHPEBUVector3@Math@UGS@@0PEAUMatrix3@23@@Z',
              (V(1, 0, 0), V(0, 1, 0)), [PV3, PV3, PM3],
              lambda r, m: (r == 1 and mat_near(m, IDENT3), 'expect rc=1 I3'))
    mtx3_case('?MTX3_init_z@@YAHPEBUVector3@Math@UGS@@PEAUMatrix3@23@@Z',
              (V(0, 0, 1),), [PV3, PM3],
              lambda r, m: (r == 1 and mat_near(m, IDENT3), 'expect rc=1 I3'))
    mtx3_case('?MTX3_init_y_z@@YAHPEBUVector3@Math@UGS@@0PEAUMatrix3@23@@Z',
              (V(0, 1, 0), V(0, 0, 1)), [PV3, PV3, PM3],
              lambda r, m: (r == 1, 'rc recorded'))
    mtx3_case('?MTX3_init_x@@YAHPEBUVector3@Math@UGS@@PEAUMatrix3@23@@Z',
              (V(1, 0, 0),), [PV3, PM3],
              lambda r, m: (r == 1, 'rc recorded'))
    mtx3_case('?MTX3_init_x_y_z@@YAHPEBUVector3@Math@UGS@@00PEAUMatrix3@23@@Z',
              (V(1, 0, 0), V(0, 1, 0), V(0, 0, 1)), [PV3, PV3, PV3, PM3],
              lambda r, m: (r == 1 and mat_near(m, IDENT3), 'expect rc=1 I3'))

    out3 = M3()
    call('?MTX3_multiply@@YAXPEBUMatrix3@Math@UGS@@0PEAU123@@Z', None,
         [PM3, PM3, PM3], ctypes.byref(M(IDENT3)), ctypes.byref(M(IDENT3)),
         ctypes.byref(out3), category='MTX')
    if getp('?MTX3_multiply@@YAXPEBUMatrix3@Math@UGS@@0PEAU123@@Z'):
        ok = mat_near(list(out3.m), IDENT3)
        add('?MTX3_multiply@@YAXPEBUMatrix3@Math@UGS@@0PEAU123@@Z', 'MTX',
            'I3*I3', {'out': list(out3.m)}, 'PASS' if ok else 'FAIL',
            'expect I3')

    out3 = M3()
    call('?MTX3_rot_about_axis@@YAXNPEBUVector3@Math@UGS@@PEAUMatrix3@23@@Z', None,
         [CDBL, PV3, PM3], math.pi / 2, ctypes.byref(V(0, 0, 1)),
         ctypes.byref(out3), category='MTX')
    if getp('?MTX3_rot_about_axis@@YAXNPEBUVector3@Math@UGS@@PEAUMatrix3@23@@Z'):
        exp = [0, -1, 0, 1, 0, 0, 0, 0, 1]
        ok = mat_near(list(out3.m), exp)
        add('?MTX3_rot_about_axis@@YAXNPEBUVector3@Math@UGS@@PEAUMatrix3@23@@Z',
            'MTX', 'rot z pi/2', {'out': list(out3.m)}, 'PASS' if ok else 'FAIL',
            'expect {0,-1,0,1,0,0,0,0,1}')

    r = call('?MTX3_is_equal@@YA_NPEBUMatrix3@Math@UGS@@0N@Z', CBOOL,
              [PM3, PM3, CDBL], ctypes.byref(M(IDENT3)), ctypes.byref(M(IDENT3)),
              1e-12, category='MTX')
    if r is not None:
        add('?MTX3_is_equal@@YA_NPEBUMatrix3@Math@UGS@@0N@Z', 'MTX', 'I3==I3',
            {'rc': bool(r)}, 'PASS' if r else 'FAIL', 'expect true')

    r = call('?MTX3_is_identity@@YA_NPEBUMatrix3@Math@UGS@@N@Z', CBOOL,
              [PM3, CDBL], ctypes.byref(M(IDENT3)), 1e-12, category='MTX')
    if r is not None:
        add('?MTX3_is_identity@@YA_NPEBUMatrix3@Math@UGS@@N@Z', 'MTX',
            'I3 identity', {'rc': bool(r)}, 'PASS' if r else 'FAIL',
            'expect true')

    out4 = M4()
    r = call('?MTX4_invert@@YAHPEBUTransformMatrix@Math@UGS@@PEAU123@@Z', CINT,
              [PM4, PM4], ctypes.byref(M4v(IDENT4)), ctypes.byref(out4),
              category='MTX')
    if r is not None:
        ok = r == 0 and mat_near(list(out4.m), IDENT4)
        add('?MTX4_invert@@YAHPEBUTransformMatrix@Math@UGS@@PEAU123@@Z', 'MTX',
            'invert I4', {'rc': r, 'out': list(out4.m)}, 'PASS' if ok else 'FAIL',
            'expect rc=0 I4')

    out4 = M4()
    call('?MTX4_multiply@@YAXPEBUTransformMatrix@Math@UGS@@0PEAU123@@Z', None,
         [PM4, PM4, PM4], ctypes.byref(M4v(IDENT4)), ctypes.byref(M4v(IDENT4)),
         ctypes.byref(out4), category='MTX')
    if getp('?MTX4_multiply@@YAXPEBUTransformMatrix@Math@UGS@@0PEAU123@@Z'):
        ok = mat_near(list(out4.m), IDENT4)
        add('?MTX4_multiply@@YAXPEBUTransformMatrix@Math@UGS@@0PEAU123@@Z', 'MTX',
            'I4*I4', {'out': list(out4.m)}, 'PASS' if ok else 'FAIL', 'expect I4')

    r = call('?MTX4_is_identity@@YA_NPEBUTransformMatrix@Math@UGS@@N@Z', CBOOL,
              [PM4, CDBL], ctypes.byref(M4v(IDENT4)), 1e-10, category='MTX')
    if r is not None:
        add('?MTX4_is_identity@@YA_NPEBUTransformMatrix@Math@UGS@@N@Z', 'MTX',
            'I4 identity', {'rc': bool(r)}, 'PASS' if r else 'FAIL', 'expect true')

    r = call('?MTX4_is_equal@@YA_NPEBUTransformMatrix@Math@UGS@@0N@Z', CBOOL,
              [PM4, PM4, CDBL], ctypes.byref(M4v(IDENT4)),
              ctypes.byref(M4v(IDENT4)), 1e-10, category='MTX')
    if r is not None:
        add('?MTX4_is_equal@@YA_NPEBUTransformMatrix@Math@UGS@@0N@Z', 'MTX',
            'I4==I4', {'rc': bool(r)}, 'PASS' if r else 'FAIL', 'expect true')

    out4 = M4()
    r = call('?MTX4_mirror@@YAHPEBUPoint3@Math@UGS@@PEBUVector3@23@PEAUTransformMatrix@23@@Z',
              CINT, [PP3, PV3, PM4], ctypes.byref(P(0, 0, 0)),
              ctypes.byref(V(0, 0, 1)), ctypes.byref(out4), category='MTX')
    if r is not None:
        exp = [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1]
        ok = r == 0 and mat_near(list(out4.m), exp)
        add('?MTX4_mirror@@YAHPEBUPoint3@Math@UGS@@PEBUVector3@23@PEAUTransformMatrix@23@@Z',
            'MTX', 'mirror z=0', {'rc': r, 'out': list(out4.m)},
            'PASS' if ok else 'FAIL', 'expect diag(1,1,-1,1)')

    r = call('?VEC3_angle_between@@YANPEBUVector3@Math@UGS@@00@Z', CDBL,
              [PV3, PV3, PV3], ctypes.byref(V(1, 0, 0)), ctypes.byref(V(0, 1, 0)),
              ctypes.byref(V(0, 0, 1)), category='VEC')
    if r is not None:
        add('?VEC3_angle_between@@YANPEBUVector3@Math@UGS@@00@Z', 'VEC',
            'angle x,y about z', {'rc': r},
            'PASS' if near(r, math.pi / 2) else 'FAIL', 'expect pi/2')

    len_out = ctypes.c_double(-1.0)
    uout = V3()
    r = call('?VEC3_unitize@@YAHPEBUVector3@Math@UGS@@NPEANPEAU123@@Z', CINT,
              [PV3, CDBL, PD, PV3], ctypes.byref(V(1, 2, 2)), 1e-10,
              ctypes.byref(len_out), ctypes.byref(uout), category='VEC')
    if r is not None:
        ok = (r == 1 and near(len_out.value, 3.0) and near(uout.x, 1 / 3)
              and near(uout.y, 2 / 3) and near(uout.z, 2 / 3))
        add('?VEC3_unitize@@YAHPEBUVector3@Math@UGS@@NPEANPEAU123@@Z', 'VEC',
            'unitize(1,2,2)', {'rc': r, 'len': len_out.value,
                                'out': [uout.x, uout.y, uout.z]},
            'PASS' if ok else 'FAIL', 'expect len=3 (1/3,2/3,2/3)')

    r = call('?VEC3_is_parallel@@YA_NPEBUVector3@Math@UGS@@0N@Z', CBOOL,
              [PV3, PV3, CDBL], ctypes.byref(V(1, 0, 0)),
              ctypes.byref(V(2, 0, 0)), 1e-10, category='VEC')
    if r is not None:
        add('?VEC3_is_parallel@@YA_NPEBUVector3@Math@UGS@@0N@Z', 'VEC',
            'parallel x,2x', {'rc': bool(r)}, 'PASS' if r else 'FAIL', 'expect true')

    r = call('?VEC3_is_perpendicular@@YA_NPEBUVector3@Math@UGS@@0N@Z', CBOOL,
              [PV3, PV3, CDBL], ctypes.byref(V(1, 0, 0)),
              ctypes.byref(V(0, 1, 0)), 1e-10, category='VEC')
    if r is not None:
        add('?VEC3_is_perpendicular@@YA_NPEBUVector3@Math@UGS@@0N@Z', 'VEC',
            'perp x,y', {'rc': bool(r)}, 'PASS' if r else 'FAIL', 'expect true')

    vout = V3()
    r = call('?VEC3_ask_perpendicular@@YAHPEBUVector3@Math@UGS@@PEAU123@@Z', CINT,
              [PV3, PV3], ctypes.byref(V(1, 0, 0)), ctypes.byref(vout),
              category='VEC')
    if r is not None:
        ok = r == 1 and near(vout.x, 0.0) and near(vout.y, 1.0) and near(vout.z, 0.0)
        add('?VEC3_ask_perpendicular@@YAHPEBUVector3@Math@UGS@@PEAU123@@Z', 'VEC',
            'perp of x', {'rc': r, 'out': [vout.x, vout.y, vout.z]},
            'PASS' if ok else 'FAIL', 'expect rc=1 (0,1,0)')

    buf = ctypes.create_string_buffer(336)
    call('??0Box3D@Math@UGS@@QEAA@XZ', ctypes.c_void_p, [ctypes.c_void_p],
         ctypes.byref(buf), category='CTOR')
    if getp('??0Box3D@Math@UGS@@QEAA@XZ'):
        raw = bytes(buf)
        vptr = struct.unpack_from('<Q', raw, 0)[0]
        mtx = struct.unpack_from('<9d', raw, 8)
        org = struct.unpack_from('<3d', raw, 80)
        ln = struct.unpack_from('<3d', raw, 104)
        dirty = raw[128]
        cached = struct.unpack_from('<Q', raw, 328)[0]
        ok = (in_module(vptr) and mat_near(mtx, IDENT3)
              and all(v == 0.0 for v in org) and all(v == 0.0 for v in ln)
              and dirty == 0 and cached == 0)
        add('??0Box3D@Math@UGS@@QEAA@XZ', 'CTOR', 'Box3D default',
            {'matrix': list(mtx), 'origin': list(org), 'length': list(ln),
             'dirty': dirty, 'cached': cached}, 'PASS' if ok else 'FAIL',
            'expect vptr in module, I3, zeros')

    src = ctypes.create_string_buffer(336)
    call('??0Box3D@Math@UGS@@QEAA@XZ', ctypes.c_void_p, [ctypes.c_void_p],
         ctypes.byref(src), category='CTOR')
    struct.pack_into('<3d', src, 80, 1.5, 2.5, 3.5)
    src[128] = b'\x01'
    dst = ctypes.create_string_buffer(336)
    call('??0Box3D@Math@UGS@@QEAA@AEBV012@@Z', ctypes.c_void_p,
         [ctypes.c_void_p, ctypes.c_void_p], ctypes.byref(dst),
         ctypes.byref(src), category='CTOR')
    if getp('??0Box3D@Math@UGS@@QEAA@AEBV012@@Z'):
        ok = bytes(dst) == bytes(src)
        add('??0Box3D@Math@UGS@@QEAA@AEBV012@@Z', 'CTOR', 'Box3D copy',
            {'bytes_equal': ok}, 'PASS' if ok else 'FAIL', 'expect 336B equal')

    dst = ctypes.create_string_buffer(336)
    mtx = M(IDENT3)
    org = P(1, 2, 3)
    lnv = (ctypes.c_double * 3)(4, 5, 6)
    call('??0Box3D@Math@UGS@@QEAA@AEBUMatrix3@12@AEBUPoint3@12@QEBN@Z',
         ctypes.c_void_p, [ctypes.c_void_p, PM3, PP3, PD], ctypes.byref(dst),
         ctypes.byref(mtx), ctypes.byref(org), lnv, category='CTOR')
    if getp('??0Box3D@Math@UGS@@QEAA@AEBUMatrix3@12@AEBUPoint3@12@QEBN@Z'):
        raw = bytes(dst)
        mtx_o = struct.unpack_from('<9d', raw, 8)
        org_o = struct.unpack_from('<3d', raw, 80)
        ln_o = struct.unpack_from('<3d', raw, 104)
        dirty_o = raw[128]
        ok = (mat_near(mtx_o, IDENT3) and org_o == (1.0, 2.0, 3.0)
              and ln_o == (4.0, 5.0, 6.0) and dirty_o == 0)
        add('??0Box3D@Math@UGS@@QEAA@AEBUMatrix3@12@AEBUPoint3@12@QEBN@Z', 'CTOR',
            'Box3D(mtx,origin,len)', {'matrix': list(mtx_o), 'origin': list(org_o),
                                       'length': list(ln_o), 'dirty': dirty_o},
            'PASS' if ok else 'FAIL', 'expect I3 (1,2,3) (4,5,6)')

    vf = ctypes.create_string_buffer(12)
    call('??0Vector3f@Math@UGS@@QEAA@XZ', ctypes.c_void_p, [ctypes.c_void_p],
         ctypes.byref(vf), category='CTOR')
    if getp('??0Vector3f@Math@UGS@@QEAA@XZ'):
        vals = struct.unpack_from('<3f', bytes(vf), 0)
        ok = vals == (0.0, 0.0, 0.0)
        add('??0Vector3f@Math@UGS@@QEAA@XZ', 'CTOR', 'Vector3f default',
            {'xyz': list(vals)}, 'PASS' if ok else 'FAIL', 'expect (0,0,0)')

    vf = ctypes.create_string_buffer(12)
    call('??0Vector3f@Math@UGS@@QEAA@MMM@Z', ctypes.c_void_p,
         [ctypes.c_void_p, ctypes.c_float, ctypes.c_float, ctypes.c_float],
         ctypes.byref(vf), 1.5, 2.5, 3.5, category='CTOR')
    if getp('??0Vector3f@Math@UGS@@QEAA@MMM@Z'):
        vals = struct.unpack_from('<3f', bytes(vf), 0)
        ok = vals == (1.5, 2.5, 3.5)
        add('??0Vector3f@Math@UGS@@QEAA@MMM@Z', 'CTOR', 'Vector3f(1.5,2.5,3.5)',
            {'xyz': list(vals)}, 'PASS' if ok else 'FAIL', 'expect (1.5,2.5,3.5)')

    vd = ctypes.create_string_buffer(12)
    call('??0Vector3f@Math@UGS@@QEAA@NNN@Z', ctypes.c_void_p,
         [ctypes.c_void_p, CDBL, CDBL, CDBL], ctypes.byref(vd), 1.25, 2.5, 3.75,
         category='CTOR')
    if getp('??0Vector3f@Math@UGS@@QEAA@NNN@Z'):
        vals = struct.unpack_from('<3f', bytes(vd), 0)
        ok = vals == (1.25, 2.5, 3.75)
        add('??0Vector3f@Math@UGS@@QEAA@NNN@Z', 'CTOR', 'Vector3f(1.25,2.5,3.75)',
            {'xyz': list(vals)}, 'PASS' if ok else 'FAIL', 'expect (1.25,2.5,3.75)')

    vc = ctypes.create_string_buffer(12)
    call('??0Vector3f@Math@UGS@@QEAA@AEBU012@@Z', ctypes.c_void_p,
         [ctypes.c_void_p, ctypes.c_void_p], ctypes.byref(vc), ctypes.byref(vf),
         category='CTOR')
    if getp('??0Vector3f@Math@UGS@@QEAA@AEBU012@@Z'):
        ok = bytes(vc) == bytes(vf)
        add('??0Vector3f@Math@UGS@@QEAA@AEBU012@@Z', 'CTOR', 'Vector3f copy',
            {'bytes_equal': ok}, 'PASS' if ok else 'FAIL', 'expect 12B equal')

    r = call('?merrorlevel@@YAHXZ', CINT, [], category='ERROR')
    if r is not None:
        add('?merrorlevel@@YAHXZ', 'ERROR', 'merrorlevel', {'rc': r},
            'PASS' if r == 0 else 'FAIL', 'expect 0')

    r = call('?merrornum@@YAHXZ', CINT, [], category='ERROR')
    if r is not None:
        add('?merrornum@@YAHXZ', 'ERROR', 'merrornum', {'rc': r},
            'PASS' if r == 0 else 'FAIL', 'expect 0')

    msg = ctypes.create_string_buffer(b'g5_smoke')
    call('?merrorpush@@YAXQEADHH@Z', None, [ctypes.c_char_p, CINT, CINT],
         ctypes.cast(msg, ctypes.c_char_p), 7, 2, category='ERROR')
    if getp('?merrorpush@@YAXQEADHH@Z'):
        lv = call('?merrorlevel@@YAHXZ', CINT, [], category='ERROR')
        num = call('?merrornum@@YAHXZ', CINT, [], category='ERROR')
        ok = lv == 2 and num == 7
        add('?merrorpush@@YAXQEADHH@Z', 'ERROR', 'push(7,2)',
            {'level': lv, 'num': num}, 'PASS' if ok else 'FAIL', 'expect 2,7')

    r = call('?merrorflush@@YAHXZ', CINT, [], category='ERROR')
    if r is not None:
        lv = call('?merrorlevel@@YAHXZ', CINT, [], category='ERROR')
        num = call('?merrornum@@YAHXZ', CINT, [], category='ERROR')
        ok = r == 0 and lv == 0 and num == 0
        add('?merrorflush@@YAHXZ', 'ERROR', 'flush',
            {'rc': r, 'level': lv, 'num': num}, 'PASS' if ok else 'FAIL',
            'expect 0/0/0')

    r = call('?EQ_ask_number_tolerance@@YANXZ', CDBL, [], category='ERROR')
    if r is not None:
        add('?EQ_ask_number_tolerance@@YANXZ', 'ERROR', 'number tolerance',
            {'rc': r}, 'PASS' if r > 0 else 'FAIL', 'expect positive')

    keep = []
    try:
        DTOR = ctypes.WINFUNCTYPE(ctypes.c_void_p, ctypes.c_void_p, ctypes.c_uint)
        LENF = ctypes.WINFUNCTYPE(ctypes.c_double, ctypes.c_void_p)
        NUMF = ctypes.WINFUNCTYPE(ctypes.c_int, ctypes.c_void_p)

        def dtor(this, flags):
            return None

        def ask_len(this):
            return ctypes.cast(this + 8, ctypes.POINTER(ctypes.c_double))[0]

        def ask_sq(this):
            return ctypes.cast(this + 0x10, ctypes.POINTER(ctypes.c_double))[0]

        def ask_num(this):
            return ctypes.cast(this + 0x18, ctypes.POINTER(ctypes.c_int))[0]

        keep = [DTOR(dtor), LENF(ask_len), LENF(ask_sq), NUMF(ask_num)]
        fake = ctypes.create_string_buffer(0x20)
        vtbl = (ctypes.c_void_p * 4)(*[ctypes.cast(f, ctypes.c_void_p) for f in keep])
        struct.pack_into('<Q', fake, 0, ctypes.cast(vtbl, ctypes.c_void_p).value)
        struct.pack_into('<d', fake, 8, 1.0e-6)
        struct.pack_into('<d', fake, 0x10, 1.0e-12)
        struct.pack_into('<i', fake, 0x18, 1)
        GETTOL = '?GetThreadTolerances@Math@UGS@@YAPEAVITolerances@12@XZ'
        SETTOL = ('?SetGlobalTolerances@Math@UGS@@YAX$$QEAV?$unique_ptr@VITolerances@Math@UGS@@'
                  'U?$default_delete@VITolerances@Math@UGS@@@std@@@std@@@Z')
        before = call(GETTOL, ctypes.c_void_p, [], category='ERROR')
        if before is not None:
            add(GETTOL, 'ERROR', 'before init',
                {'ptr': hex(before) if before else None},
                'PASS' if not before else 'FAIL', 'expect NULL')
        slot = (ctypes.c_void_p * 1)(ctypes.cast(fake, ctypes.c_void_p))
        call(SETTOL, None, [ctypes.c_void_p], ctypes.byref(slot), category='ERROR')
        if getp(SETTOL):
            got = call(GETTOL, ctypes.c_void_p, [], category='ERROR')
            ok = got == ctypes.cast(fake, ctypes.c_void_p).value
            add(SETTOL, 'ERROR', 'install fake tolerance',
                {'GetThreadTolerances': hex(got) if got else None},
                'PASS' if ok else 'FAIL', 'expect fake address')
            r2 = call('?EQ_ask_length_tolerance@@YANXZ', CDBL, [], category='ERROR')
            if r2 is not None:
                add('?EQ_ask_length_tolerance@@YANXZ', 'ERROR', 'after init',
                    {'rc': r2}, 'PASS' if near(r2, 1.0e-6, 1e-18) else 'FAIL',
                    'expect 1e-6')
            r3 = call('?EQ_ask_number_tolerance@@YANXZ', CDBL, [], category='ERROR')
            if r3 is not None:
                add('?EQ_ask_number_tolerance@@YANXZ', 'ERROR', 'after init',
                    {'rc': r3}, 'PASS' if near(r3, 1.0e-10, 1e-18) else 'FAIL',
                    'expect 1e-10')
            slot2 = (ctypes.c_void_p * 1)(None)
            call(SETTOL, None, [ctypes.c_void_p], ctypes.byref(slot2), category='ERROR')
            got2 = call(GETTOL, ctypes.c_void_p, [], category='ERROR')
            if got2 is not None:
                add(SETTOL + ' restore', 'ERROR', 'restore nullptr',
                    {'ptr': hex(got2) if got2 else None},
                    'PASS' if not got2 else 'FAIL', 'expect NULL')
    except Exception as e:
        add('SetGlobalTolerances path', 'ERROR', 'init/restore', None, 'FAIL', repr(e))

    total = len(report['tests'])
    passed = sum(1 for t in report['tests'] if t['verdict'] == 'PASS')
    failed = total - passed
    report['summary'] = {'total': total, 'pass': passed, 'fail': failed}
    if not args.quiet:
        for t in report['tests']:
            print('%-4s %-6s %s' % (t['verdict'], t['category'], t['name']))
            if t['verdict'] != 'PASS':
                print('     detail:', t.get('detail'))
        print('load:', report['load_rc'], 'libsyss:', report['libsyss_path'])
        print('RESULT: %s (%d/%d PASS)'
              % ('PASS' if failed == 0 else 'FAIL', passed, total))
    if args.json:
        with open(args.json, 'w', encoding='utf-8') as f:
            json.dump(report, f, ensure_ascii=False, indent=1)
        if not args.quiet:
            print('json:', args.json)
    return 0 if failed == 0 else 1


if __name__ == '__main__':
    sys.exit(main())
