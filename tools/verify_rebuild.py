#!/usr/bin/env python3
"""Verify that bin/libugmath.dll can be reproduced from src/ (build determinism gate).

Steps:
  1. Rebuild the DLL from the package source tree (build/build_static.py -> build/build_link_r8.py)
     in a temp directory.
  2. Compare the rebuilt DLL against bin/libugmath.dll:
     - normalize the two known timestamp fields (PE header TimeDateStamp and the
       IMAGE_DEBUG_DIRECTORY TimeDateStamp copy), then require byte-identical output;
     - section-by-section comparison (text/rdata/data/pdata);
     - export-table equality (reuses verify_exports).
Exit code 0 on PASS, 1 on FAIL.

Usage:
  python -X utf8 tools/verify_rebuild.py             # full rebuild + compare
  python -X utf8 tools/verify_rebuild.py --skip-build --rebuilt <dll>   # compare only
"""
import argparse
import hashlib
import os
import struct
import subprocess
import sys
import tempfile
import shutil

HERE = os.path.dirname(os.path.abspath(__file__))
PKG = os.path.dirname(HERE)


def sha256(b):
    return hashlib.sha256(b).hexdigest()


def parse_pe(d):
    pe = struct.unpack_from('<I', d, 0x3c)[0]
    nsec = struct.unpack_from('<H', d, pe + 6)[0]
    opt = pe + 24
    magic = struct.unpack_from('<H', d, opt)[0]
    dd = opt + (112 if magic == 0x20b else 96)
    secs = []
    so = opt + struct.unpack_from('<H', d, pe + 20)[0]
    for i in range(nsec):
        b = so + i * 40
        name = d[b:b + 8].rstrip(b'\x00').decode(errors='replace')
        vsz = struct.unpack_from('<I', d, b + 8)[0]
        va = struct.unpack_from('<I', d, b + 12)[0]
        rsz = struct.unpack_from('<I', d, b + 16)[0]
        ra = struct.unpack_from('<I', d, b + 20)[0]
        secs.append((name, va, vsz, ra, rsz))
    return pe, dd, secs


def rva2off(secs, rva):
    for name, va, vsz, ra, rsz in secs:
        if va <= rva < va + max(vsz, rsz):
            return ra + (rva - va)
    return None


def timestamp_offsets(d):
    """Return file offsets of the two build-timestamp fields."""
    pe, dd, secs = parse_pe(d)
    offs = [pe + 8]  # PE header TimeDateStamp
    dbg_rva, dbg_sz = struct.unpack_from('<II', d, dd + 6 * 8)
    if dbg_rva and dbg_sz >= 28:
        o = rva2off(secs, dbg_rva)
        if o is not None:
            offs.append(o + 4)  # IMAGE_DEBUG_DIRECTORY.TimeDateStamp
    return offs


def normalized(d):
    buf = bytearray(d)
    for o in timestamp_offsets(d):
        struct.pack_into('<I', buf, o, 0)
    return bytes(buf)


def diff_report(a, b, limit=16):
    n = min(len(a), len(b))
    diffs = [i for i in range(n) if a[i] != b[i]]
    if len(a) != len(b):
        diffs.extend(range(n, max(len(a), len(b))))
    return diffs[:limit], len(diffs)


def export_names(path):
    d = open(path, 'rb').read()
    pe, dd, secs = parse_pe(d)
    exp_rva, exp_sz = struct.unpack_from('<II', d, dd)
    if not exp_rva:
        return set()
    eo = rva2off(secs, exp_rva)
    nname = struct.unpack_from('<I', d, eo + 0x18)[0]
    names_rva = struct.unpack_from('<I', d, eo + 0x20)[0]
    no = rva2off(secs, names_rva)
    names = set()
    for i in range(nname):
        nr = struct.unpack_from('<I', d, no + 4 * i)[0]
        o = rva2off(secs, nr)
        end = d.index(b'\x00', o)
        names.add(d[o:end].decode(errors='replace'))
    return names


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--skip-build', action='store_true')
    ap.add_argument('--rebuilt', default=None)
    args = ap.parse_args()

    ref = os.path.join(PKG, 'bin', 'libugmath.dll')
    if not os.path.isfile(ref):
        print('FAIL: missing %s' % ref)
        return 1

    if args.skip_build:
        if not args.rebuilt or not os.path.isfile(args.rebuilt):
            print('FAIL: --skip-build requires --rebuilt <dll>')
            return 1
        rebuilt = args.rebuilt
        tmpdir = None
    else:
        tmpdir = tempfile.mkdtemp(prefix='ugm_rebuild_')
        try:
            # Copy only what the build needs: src/ + build/
            for sub in ('src', 'build', 'third_party'):
                shutil.copytree(os.path.join(PKG, sub), os.path.join(tmpdir, sub))
            env = dict(os.environ)
            for script in ('build_static.py', 'build_link_r8.py'):
                p = os.path.join(tmpdir, 'build', script)
                print('--- running %s' % script)
                r = subprocess.run([sys.executable, '-I', p], cwd=tmpdir,
                                   capture_output=True, text=True, errors='replace')
                if r.returncode != 0:
                    print('FAIL: %s rc=%d' % (script, r.returncode))
                    print((r.stderr or r.stdout or '')[-4000:])
                    return 1
            rebuilt = os.path.join(tmpdir, 'build', 'out', 'libugmath.dll')
            if not os.path.isfile(rebuilt):
                print('FAIL: rebuilt DLL not found')
                return 1
        except Exception:
            raise
        finally:
            pass  # keep tmpdir for debugging

    a = open(ref, 'rb').read()
    b = open(rebuilt, 'rb').read()
    print('reference : %s  (%d bytes, sha256 %s)' % (ref, len(a), sha256(a)))
    print('rebuilt   : %s  (%d bytes, sha256 %s)' % (rebuilt, len(b), sha256(b)))

    ok = True

    # 1) normalized byte-identity
    na, nb = normalized(a), normalized(b)
    norm_eq = na == nb
    print('[gate1] normalized byte-identity (PE + debug-directory timestamps zeroed): %s'
          % ('PASS' if norm_eq else 'FAIL'))
    if norm_eq:
        print('        normalized sha256: %s' % sha256(na))
    else:
        first, total = diff_report(na, nb)
        print('        differing bytes: %d, first offsets: %s' % (
            total, ', '.join('0x%x' % x for x in first)))
        ok = False

    # 2) section-by-section equality
    _, _, secs_a = parse_pe(a)
    same_secs = len(a) == len(b)
    print('[gate2] section-by-section comparison:')
    for name, va, vsz, ra, rsz in secs_a:
        end = min(ra + rsz, len(a), len(b))
        same = a[ra:end] == b[ra:end]
        print('        %-10s raw=%7d  %s' % (name, rsz, 'equal' if same else 'DIFFER'))
        if not same and name not in ('.rdata',):
            ok = False
        if not same and name == '.rdata':
            # allowed: the debug-directory timestamp copy inside .rdata
            da = bytearray(na[ra:end]); db_ = bytearray(nb[ra:end])
            if da != db_:
                ok = False

    # 3) export table equality
    ea, eb = export_names(ref), export_names(rebuilt)
    exp_eq = ea == eb
    print('[gate3] export table: raw=%d names, rebuilt=%d names, missing=%d, extra=%d -> %s'
          % (len(ea), len(eb), len(ea - eb), len(eb - ea), 'PASS' if exp_eq else 'FAIL'))
    if not exp_eq:
        ok = False

    print('RESULT:', 'PASS' if ok else 'FAIL')
    return 0 if ok else 1


if __name__ == '__main__':
    sys.exit(main())
