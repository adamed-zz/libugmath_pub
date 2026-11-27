import argparse
import hashlib
import json
import struct
import sys
import time


def sha256_file(path):
    h = hashlib.sha256()
    with open(path, 'rb') as f:
        for chunk in iter(lambda: f.read(1 << 20), b''):
            h.update(chunk)
    return h.hexdigest()


def parse_exports(path):
    data = open(path, 'rb').read()
    if len(data) < 0x40 or data[:2] != b'MZ':
        raise SystemExit('not a PE file: %s' % path)
    e = struct.unpack_from('<I', data, 0x3C)[0]
    if data[e:e + 4] != b'PE\0\0':
        raise SystemExit('missing PE signature: %s' % path)
    coff = e + 4
    nsect = struct.unpack_from('<H', data, coff + 2)[0]
    optsz = struct.unpack_from('<H', data, coff + 16)[0]
    opt = coff + 20
    magic = struct.unpack_from('<H', data, opt)[0]
    if magic == 0x20b:
        dd = opt + 112
    elif magic == 0x10b:
        dd = opt + 96
    else:
        raise SystemExit('unknown optional header magic 0x%x: %s' % (magic, path))
    exp_rva, exp_size = struct.unpack_from('<II', data, dd)
    sections = []
    sec = opt + optsz
    for i in range(nsect):
        o = sec + i * 40
        vs, va, rs, ro = struct.unpack_from('<IIII', data, o + 8)
        sections.append((va, vs, ro, rs))

    def rva2off(rva):
        for va, vs, ro, rs in sections:
            if va <= rva < va + max(vs, rs):
                return rva - va + ro
        raise SystemExit('RVA 0x%x not mapped: %s' % (rva, path))

    if not exp_rva or not exp_size:
        return [], 0
    ed = rva2off(exp_rva)
    base, nfunc, nname, afunc, aname, aord = struct.unpack_from('<IIIIII', data, ed + 0x10)
    funcs = [struct.unpack_from('<I', data, rva2off(afunc) + 4 * i)[0]
             for i in range(nfunc)]
    entries = []
    named = set()
    for i in range(nname):
        nrva = struct.unpack_from('<I', data, rva2off(aname) + 4 * i)[0]
        ordv = struct.unpack_from('<H', data, rva2off(aord) + 2 * i)[0]
        off = rva2off(nrva)
        end = data.find(b'\0', off)
        nm = data[off:end].decode('ascii', 'replace')
        fwd = None
        if exp_rva <= funcs[ordv] < exp_rva + exp_size:
            foff = rva2off(funcs[ordv])
            fend = data.find(b'\0', foff)
            fwd = data[foff:fend].decode('ascii', 'replace')
        entries.append({'ordinal': base + ordv, 'name': nm, 'forwarder': fwd})
        named.add(base + ordv)
    for i in range(nfunc):
        if base + i not in named:
            entries.append({'ordinal': base + i, 'name': None, 'forwarder': None})
    return entries, base


def parse_list(path):
    entries = []
    with open(path, encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            parts = line.split(None, 1)
            if parts[0].isdigit():
                entries.append({'ordinal': int(parts[0]),
                                'name': parts[1].strip() if len(parts) > 1 else None,
                                'forwarder': None})
            else:
                entries.append({'ordinal': None, 'name': line, 'forwarder': None})
    return entries, None


def compare(ref, new):
    ref_names = sorted(e['name'] for e in ref if e['name'])
    new_names = sorted(e['name'] for e in new if e['name'])
    ref_set = set(ref_names)
    new_set = set(new_names)
    missing = sorted(ref_set - new_set)
    extra = sorted(new_set - ref_set)
    mismatch = []
    if ref and all(e['ordinal'] is not None for e in ref):
        ref_map = {e['name']: e['ordinal'] for e in ref if e['name']}
        new_map = {e['name']: e['ordinal'] for e in new if e['name']}
        for nm in sorted(ref_set & new_set):
            if ref_map.get(nm) != new_map.get(nm):
                mismatch.append({'name': nm, 'ref_ordinal': ref_map.get(nm),
                                 'new_ordinal': new_map.get(nm)})
    ok = (not missing and not extra and not mismatch
          and len(ref_names) == len(new_names))
    return {'pass': ok, 'missing': missing, 'extra': extra,
            'ordinal_mismatch': mismatch,
            'ref_named': len(ref_names), 'new_named': len(new_names),
            'ref_total': len(ref), 'new_total': len(new)}


def main(argv=None):
    ap = argparse.ArgumentParser()
    src = ap.add_mutually_exclusive_group(required=True)
    src.add_argument('--raw', help='original libugmath.dll')
    src.add_argument('--raw-list', help='frozen export list (ordinal name)')
    src.add_argument('--raw-json', help='JSON produced by this tool')
    ap.add_argument('--new', required=True, help='DLL to verify')
    ap.add_argument('--json', help='write result JSON here')
    ap.add_argument('--quiet', action='store_true')
    args = ap.parse_args(argv)
    if args.raw:
        ref, ref_base = parse_exports(args.raw)
        ref_src = {'source': args.raw, 'sha256': sha256_file(args.raw),
                   'ordinal_base': ref_base}
    elif args.raw_list:
        ref, ref_base = parse_list(args.raw_list)
        ref_src = {'source': args.raw_list,
                   'sha256': sha256_file(args.raw_list),
                   'ordinal_base': ref_base}
    else:
        doc = json.load(open(args.raw_json, encoding='utf-8'))
        ref = doc['ref_exports']
        ref_base = doc.get('ref_ordinal_base')
        ref_src = {'source': args.raw_json,
                   'sha256': doc.get('reference', {}).get('sha256'),
                   'ordinal_base': ref_base}
    new, new_base = parse_exports(args.new)
    cmp = compare(ref, new)
    result = {
        'tool': 'verify_exports.py',
        'generated_utc': time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime()),
        'reference': ref_src,
        'new': {'source': args.new, 'sha256': sha256_file(args.new),
                'ordinal_base': new_base},
        'result': cmp,
        'ref_exports': [{'ordinal': e['ordinal'], 'name': e['name']}
                        for e in sorted(ref, key=lambda x: (x['ordinal'] or 0,
                                                           x['name'] or ''))],
    }
    if not args.quiet:
        print('reference: %s (%d exports)' % (ref_src['source'], cmp['ref_total']))
        print('new      : %s (%d exports)' % (args.new, cmp['new_total']))
        print('missing  : %d' % len(cmp['missing']))
        print('extra    : %d' % len(cmp['extra']))
        print('ordinal_mismatch: %d' % len(cmp['ordinal_mismatch']))
        for nm in cmp['missing'][:20]:
            print('  MISSING', nm)
        for nm in cmp['extra'][:20]:
            print('  EXTRA  ', nm)
        for mm in cmp['ordinal_mismatch'][:20]:
            print('  ORDINAL', mm['name'], mm['ref_ordinal'], '->',
                  mm['new_ordinal'])
        print('RESULT: %s' % ('PASS' if cmp['pass'] else 'FAIL'))
    if args.json:
        with open(args.json, 'w', encoding='utf-8') as f:
            json.dump(result, f, ensure_ascii=False, indent=1)
        if not args.quiet:
            print('json:', args.json)
    return 0 if cmp['pass'] else 1


if __name__ == '__main__':
    sys.exit(main())
