import argparse
import glob
import os
import shutil
import subprocess
import sys
import time
from concurrent.futures import ProcessPoolExecutor, as_completed

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import build_env

PKG = os.path.dirname(HERE)
SRC = os.path.join(PKG, 'src', 'ugmath', 'src')
INC1 = os.path.join(PKG, 'src', 'ugmath', 'include')
INC2 = os.path.join(INC1, 'ugmath')
OBJ = os.path.join(HERE, 'obj')
FLAGS = '/nologo /c /O2 /EHsc /std:c++20 /utf-8 /MD /GS-'.split()
EXTRA_SOURCES = ['aliases2.cpp', 'aliases2b.cpp', 'aliases3.cpp', 'aliases4.cpp']


def _obj_for(path):
    return os.path.join(OBJ, os.path.splitext(os.path.basename(path))[0] + '.obj')


def _fresh(src, obj):
    return os.path.exists(obj) and os.path.getmtime(obj) > os.path.getmtime(src)


def one(cpp):
    obj = _obj_for(cpp)
    if _fresh(cpp, obj):
        return (cpp, 0, 'cached')
    env = build_env.get_env()
    cl = build_env.tool('cl.exe')
    args = [cl] + FLAGS + ['/I' + INC1, '/I' + INC2, '/Fo' + obj, cpp]
    p = subprocess.run(args, capture_output=True, text=True, errors='replace', env=env)
    return (cpp, p.returncode, ((p.stdout or '') + (p.stderr or ''))[-1500:])


def main(argv=None):
    ap = argparse.ArgumentParser()
    ap.add_argument('--clean', action='store_true')
    ap.add_argument('--jobs', type=int, default=0)
    args = ap.parse_args(argv)
    if args.clean and os.path.isdir(OBJ):
        shutil.rmtree(OBJ)
    os.makedirs(OBJ, exist_ok=True)
    os.environ.update(build_env.get_env())
    cpps = sorted(glob.glob(os.path.join(SRC, '*.cpp')))
    cpps += [os.path.join(HERE, n) for n in EXTRA_SOURCES
             if os.path.isfile(os.path.join(HERE, n))]
    jobs = args.jobs or min(16, os.cpu_count() or 4)
    print('sources', len(cpps), 'jobs', jobs)
    fails = []
    t0 = time.time()
    with ProcessPoolExecutor(max_workers=jobs) as ex:
        futs = [ex.submit(one, f) for f in cpps]
        done = 0
        for fu in as_completed(futs):
            cpp, rc, out = fu.result()
            done += 1
            if rc != 0:
                fails.append((cpp, out))
                print('FAIL', os.path.basename(cpp))
            if done % 100 == 0:
                print('progress', done, 'fails', len(fails), 'elapsed %.1fs' % (time.time() - t0))
    print('DONE', len(cpps), 'fails', len(fails), 'elapsed %.1fs' % (time.time() - t0))
    if fails:
        path = os.path.join(HERE, 'build_fails.txt')
        with open(path, 'w', encoding='utf-8') as f:
            for src, out in fails:
                f.write('==== %s\n%s\n' % (src, out))
        print('see', path)
        return 1
    return 0


if __name__ == '__main__':
    sys.exit(main())
