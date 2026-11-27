import glob
import os
import re
import struct
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import build_env

PKG = os.path.dirname(HERE)
OBJ = os.path.join(HERE, 'obj')
WORK = os.path.join(HERE, 'work')
OUT = os.path.join(HERE, 'out')

ASM_RETIRED = {
    'link_extra.obj',
    'asm_072ec0.obj', 'asm_073910.obj', 'asm_08a960.obj', 'asm_08cf30.obj',
    'asm_0906d0.obj', 'asm_091070.obj', 'asm_0923b0.obj', 'asm_0938c0.obj',
    'asm_1eea0.obj', 'asm_76ea0.obj', 'asm_7750.obj', 'asm_7a860.obj',
    'asm_7ee70.obj', 'asm_81830.obj', 'asm_data_7750.obj', 'asm_data_b11r.obj',
    'asm_data_b12r.obj', 'asm_data_delivery.obj',
    'b14_b044_delivery.obj', 'b14_b14_abs.obj', 'b14_b14_data.obj',
    'b14_b84c0_impl.obj', 'b14_b84c0_thunk.obj',
    'b15_asm_0913a2_delivery.obj', 'b15_b15_abs.obj',
    'b16_asm_786b0_delivery.obj', 'b17_asm_786b0_delivery.obj',
    'b18_asm_743e0_delivery.obj',
    'b19_asm_7d300_delivery.obj', 'b19_asm_7e510_delivery.obj',
    'b19_asm_80a00_delivery.obj', 'b19_asm_80de0_delivery.obj',
    'data_exports.obj',
    'gap2.obj', 'gap2_vt.obj', 'h003.obj',
    'vectormagnitude_double.obj', 'vectormagnitude_float.obj',
    'sub_180001530.obj', 'sub_180001820.obj', 'sub_180019820.obj',
    'sub_180033720.obj', 'sub_180036070.obj', 'sub_180050c50.obj',
    'sub_180052030.obj', 'sub_1800540a0.obj', 'sub_180054c60.obj',
    'sub_180055700.obj', 'sub_18005fc00.obj', 'sub_180060000.obj',
    'sub_180060490.obj', 'sub_180061400.obj', 'sub_18009c3e0.obj',
    'sub_1800ac240.obj',
    'cxx_sub_180073910.obj',
    'sub_1800764d0.obj', 'h0913a2.obj', 'sub_1800786b0.obj', 'sub_1800743e0.obj',
    'sub_18007d300.obj', 'sub_18007e510.obj', 'sub_180080a00.obj', 'sub_180080de0.obj',
}


def neutralize_lsfit_severe_dtor(objs):
    target = b'??1Severe@Error@UGS@@UEAA@XZ'
    outdir = os.path.join(WORK, 'obj_f1')
    os.makedirs(outdir, exist_ok=True)
    patched = {}
    for path in objs:
        data = bytearray(open(path, 'rb').read())
        if len(data) < 18:
            continue
        try:
            machine, nsect, ts, symptr, nsym, optsz = struct.unpack('<HHIIIH', data[:18])
        except struct.error:
            continue
        if machine != 0x8664 or nsym == 0:
            continue
        sec = 20 + optsz
        strtab = symptr + nsym * 18
        if strtab > len(data):
            continue
        hit = False
        for i in range(nsym):
            e = symptr + i * 18
            if e + 18 > len(data):
                break
            name8, val, secnum, typ, cls, naux = struct.unpack('<8sIhHBB', data[e:e+18])
            if name8[:4] == b'\0\0\0\0':
                noff = struct.unpack('<I', name8[4:8])[0]
                if strtab + noff >= len(data):
                    continue
                end = data.find(b'\0', strtab + noff)
                if end < 0:
                    continue
                nm = data[strtab + noff:end]
            else:
                nm = name8.rstrip(b'\0')
            if nm == target and secnum > 0:
                struct.pack_into('<h', data, e + 12, 0)
                if 1 <= secnum <= nsect:
                    coff = sec + (secnum - 1) * 40 + 36
                    ch = struct.unpack('<I', data[coff:coff + 4])[0]
                    struct.pack_into('<I', data, coff, ch & ~0x1000)
                hit = True
        if hit:
            dst = os.path.join(outdir, os.path.basename(path))
            open(dst, 'wb').write(data)
            patched[path] = dst
    return patched


def run(exe, args, logname=None):
    env = build_env.get_env()
    p = subprocess.run([exe] + args, capture_output=True, text=True,
                       errors='replace', env=env, cwd=WORK)
    txt = (p.stdout or '') + (p.stderr or '')
    if logname:
        with open(os.path.join(WORK, logname), 'w', encoding='utf-8',
                  errors='replace') as f:
            f.write(txt)
    return p.returncode, txt


def main():
    os.makedirs(WORK, exist_ok=True)
    os.makedirs(OUT, exist_ok=True)
    libexe = build_env.tool('lib.exe')
    linkexe = build_env.tool('link.exe')
    cl = build_env.tool('cl.exe')
    objs = sorted(glob.glob(os.path.join(OBJ, '*.obj')))
    if not objs:
        print('no objects in %s; run build_static.py first' % OBJ)
        return 1
    for stale in sorted(ASM_RETIRED):
        for o in [x for x in objs if os.path.basename(x).lower() == stale]:
            retired = os.path.join(WORK, 'obj_retired')
            os.makedirs(retired, exist_ok=True)
            os.replace(o, os.path.join(retired, os.path.basename(o)))
            print('retired stale obj', o)
    objs = [x for x in objs if os.path.basename(x).lower() not in ASM_RETIRED]
    patched = neutralize_lsfit_severe_dtor(objs)
    if patched:
        print('neutralized objs', len(patched))
    objs = [patched.get(o, o) for o in objs]
    rsp = os.path.join(WORK, 'objs.rsp')
    with open(rsp, 'w', encoding='ascii') as f:
        for o in objs:
            f.write('"%s"\n' % o)
    arc = os.path.join(WORK, 'ugmath_export.lib')
    rc, txt = run(libexe, ['/nologo', '/out:' + arc, '@' + rsp], 'lib_archive.log')
    print('archive rc', rc, 'objs', len(objs))
    if rc != 0:
        print(txt[-800:])
        return 1
    defpath = os.path.join(WORK, 'f1imports.def')
    with open(defpath, 'w', encoding='ascii') as f:
        f.write('LIBRARY libsyss.dll\n')
        f.write('EXPORTS\n')
        f.write('    RDEBUG__enabled DATA\n')
        f.write('    RDEBUG_ask_flag\n')
    f1lib = os.path.join(WORK, 'f1imports.lib')
    rc, txt = run(libexe, ['/nologo', '/def:' + defpath, '/machine:x64',
                           '/out:' + f1lib], 'f1imports_lib.log')
    print('f1imports lib rc', rc)
    if rc != 0:
        print(txt[-800:])
        return 1
    libsyss_def = os.path.join(PKG, 'third_party', 'libsyss.def')
    libsyss_lib = os.path.join(WORK, 'libsyss.lib')
    if (not os.path.isfile(libsyss_lib)
            or os.path.getmtime(libsyss_lib) < os.path.getmtime(libsyss_def)):
        rc, txt = run(libexe, ['/nologo', '/def:' + libsyss_def, '/machine:x64',
                              '/out:' + libsyss_lib], 'libsyss_lib.log')
        print('libsyss lib rc', rc)
        if rc != 0:
            print(txt[-800:])
            return 1
    dm = os.path.join(HERE, 'dllmain.cpp')
    p = subprocess.run([cl, '/nologo', '/c', '/O2', '/EHsc', '/std:c++20', '/MD',
                        '/Fo' + os.path.join(WORK, 'dllmain.obj'), dm],
                       capture_output=True, text=True, errors='replace',
                       env=build_env.get_env(), cwd=WORK)
    print('dllmain rc', p.returncode)
    if p.returncode != 0:
        print(((p.stdout or '') + (p.stderr or ''))[-800:])
        return 1
    args = ['/nologo', '/DLL', '/OUT:' + os.path.join(OUT, 'libugmath.dll'),
            '/MAP:' + os.path.join(OUT, 'libugmath.map'),
            '/DEF:' + os.path.join(HERE, 'exports.def'),
            os.path.join(WORK, 'dllmain.obj'), os.path.join(OBJ, 'aliases3.obj'),
            arc, f1lib, libsyss_lib,
            'kernel32.lib', 'user32.lib', 'advapi32.lib', 'ole32.lib',
            'oleaut32.lib', 'uuid.lib', 'shell32.lib', 'gdi32.lib']
    a4 = os.path.join(OBJ, 'aliases4.obj')
    if os.path.exists(a4):
        args.append(a4)
    args += [
        '/alternatename:?sub_180001820@@YAPEANPEANNPEBN@Z=sub_180001820',
        '/alternatename:?sub_180001820@@YAPEAUPoint3@Math@UGS@@PEAU123@NPEBU123@@Z=sub_180001820',
        '/alternatename:?sub_18009FBD0@@YAXPEBN000PEAN@Z=sub_18009FBD0',
        '/alternatename:?sub_18009FBD0@@YAXPEBUPoint3@Math@UGS@@PEBUMatrix3@23@01PEAUTransformMatrix@23@@Z=sub_18009FBD0',
        '/alternatename:__imp_MACH__checking_level=__imp_?MACH__checking_level@@3HA',
        '/include:sub_180001820',
        '/include:sub_18009FBD0',
        '/alternatename:ARC_SPLINE_inter_line_line_2d=?ARC_SPLINE_inter_line_line_2d@@YAXQEBNPEBUPoint2@Math@UGS@@1HPEAUVector2@23@2PEAU123@PEAN4PEAH@Z',
        '/alternatename:dep_eqz=?eqz@@YAHPEBN0PEBH@Z',
        '/alternatename:MTX3_init_z=?MTX3_init_z@@YAHPEBUVector3@Math@UGS@@PEAUMatrix3@23@@Z',
        '/alternatename:SM_calloc=?SM_calloc@@YAPEAX_K0@Z',
        '/alternatename:sub_180050820=?sub_180050820@@YAXHPEBUPoint3@Math@UGS@@PEBN_JPEAUVector3@23@PEAU123@1PEAN@Z',
        '/alternatename:sub_180050C50=?sub_180050C50@@YAXH_JHPEBUPoint3@Math@UGS@@1PEAUVector3@23@PEANPEAU123@PEAH2@Z',
        '/alternatename:sub_180051CD0=?sub_180051CD0@@YAXH_JHPEAUPoint3@Math@UGS@@PEAUVector3@23@2PEANZZ',
        '/alternatename:sub_180052030=?sub_180052030@@YAX_JHPEBUPoint3@Math@UGS@@0NPEAUVector3@23@PEAU123@22PEAN@Z',
        '/alternatename:sub_180054C60=?sub_180054C60@@YAPEANHPEANN00PEAH@Z',
        '/alternatename:sub_1800B4DA0=?VEC2_unitize@@YAHPEBUVector2@Math@UGS@@NPEANPEAU123@@Z',
        '/alternatename:?BCDF_update_curvature_derivs@@YAXPEAUBCDF_s@@@Z=?InteriorUnconnectedEdges@Graph@Math@UGS@@QEBAXAEBTBOX3_s@@AEAV?$vector@HV?$SMAlloc@H@Memory@UGS@@@std@@1@Z',
        '/alternatename:?MultiplyMatrices@Math@UGS@@YAXQEBN0HHHQEAN@Z=?NR_matrix_2d_as_1d_product_of_2@@YAXPEAN0HHH0@Z',
        '/alternatename:?m511@@YAXPEAN0@Z=?map13@@YAXPEBNPEAN@Z',
        '/alternatename:?MTX3_init_roll_pitch_yaw_impl@@YAXNNNNNNPEAUMatrix3@Math@UGS@@@Z=sub_18009C190',
        '/alternatename:?DGEOM_convert_crvatr_to_radius@@YAHQEAN0@Z=?DGEOM_convert_radius_to_crvatr@@YAHQEAN0@Z',
        '/include:sub_18009C190',
        '/include:?InteriorUnconnectedEdges@Graph@Math@UGS@@QEBAXAEBTBOX3_s@@AEAV?$vector@HV?$SMAlloc@H@Memory@UGS@@@std@@1@Z',
        '/include:?map13@@YAXPEBNPEAN@Z',
        '/alternatename:?sub_6A8D0@@YAXXZ=sub_18006A8D0',
        '/alternatename:?sub_1B780@@YAXXZ=sub_18001B780',
        '/alternatename:?LSFIT_internal_1820@@YA?AUVector3@Math@UGS@@NPEBU123@@Z=sub_180001820',
        '/alternatename:?sub_1800AB130@@YAXHPEAUSOLVE_complex@@0_N@Z=sub_1800AB130',
        '/alternatename:?sub_1800AAF80@@YAHHPEAUSOLVE_complex@@PEAN@Z=sub_1800AAF80',
        '/alternatename:?sub_1800AC240@@YAHPEBNPEAN@Z=sub_1800AC240',
        '/alternatename:?LSFIT_ask_principle_axes_of_inertia_from_3d_pts@@YAXHPEBUPoint3@Math@UGS@@PEAU123@QEANQEAUVector3@23@@Z=?LSFIT_ask_principle_axes_of_inertia_from_3d_pts@@YAXHPEAUPoint3@Math@UGS@@0QEANQEAUVector3@23@@Z',
        '/alternatename:?LSFIT_plane_to_points@@YAXHPEBUPoint3@Math@UGS@@HPEAU123@PEAUVector3@23@PEAHPEAN@Z=?LSFIT_plane_to_points@@YAXHPEAUPoint3@Math@UGS@@H0PEAUVector3@23@PEAHPEAN@Z',
        '/alternatename:?LSFIT_ask_mean_vec@@YAXHPEBUVector3@Math@UGS@@_NPEAU123@PEAN@Z=?LSFIT_ask_mean_vec@@YAXHPEAUVector3@Math@UGS@@_N0PEAN@Z',
        '/alternatename:?NR_2d_matrix_allo@@YAPEAPEANHHPEAPEAPEAN@Z=?NR_2d_matrix_allo@@YAPEAPEANHHPEAPEAN@Z',
        '/alternatename:?product_of_2@@YAXPEBN0HHHPEAN@Z=?NR_matrix_2d_as_1d_product_of_2@@YAXPEAN0HHH0@Z',
        '/alternatename:?copy_1d_to_2d@@YAXPEBNHHPEAPEAN@Z=?NR_matrix_copy_1d_to_2d@@YAXPEANHHPEAPEAN@Z',
        '/alternatename:?NR_ask_eigenvalues_jacobi@@YAXPEAPEANHHPEAN0PEAH@Z=?NR_ask_eigenvalues_jacobi@@YAXPEAPEANHHQEAN0PEAH@Z',
        '/include:sub_180001820',
        '/include:sub_1800AB130',
        '/include:sub_1800AB530',
        '/include:b24_assign_int',
        '/include:sub_18007DDB0',
        '/include:sub_180033610',
        '/include:sub_180033560',
        '/include:b24_graph_default',
        '/include:??1Precondition@Error@UGS@@UEAA@XZ',
        '/include:b24_assign_double',
        '/include:b24_pop_heap_hole_ip3',
        '/include:sub_180082A90',
        '/include:sub_18008B2A0',
        '/include:sub_18008B2E0',
        '/include:sub_180094940',
        '/include:sub_18008A960',
        '/include:sub_180093E90',
        '/include:sub_1800923B0',
        '/include:sub_1800906D0',
        '/include:sub_180091070',
        '/include:sub_18008CF30',
        '/include:sub_1800B84C0',
        '/include:sub_180072EC0',
        '/include:sub_180073910',
        '/include:sub_1800938C0',
        '/include:sub_1800786B0',
    ]
    rc, txt = run(linkexe, args, 'link_strict_r8.log')
    n2019 = len(re.findall(r'LNK2019', txt))
    n2001 = len(re.findall(r'LNK2001', txt))
    n2005 = len(re.findall(r'LNK2005', txt))
    n1120 = re.findall(r'LNK1120:\s*(\d+)', txt)
    print('link rc', rc, 'LNK2019', n2019, 'LNK2001', n2001,
          'LNK2005', n2005, 'LNK1120', n1120)
    return 0 if rc == 0 else 1


if __name__ == '__main__':
    sys.exit(main())
