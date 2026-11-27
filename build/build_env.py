import os
import shutil
import subprocess

HERE = os.path.dirname(os.path.abspath(__file__))
PKG = os.path.dirname(HERE)

DEFAULT_MSVC_VER = os.environ.get('UGMATH_MSVC_VER', '14.29')
KITS_VER = os.environ.get('UGMATH_SDK_VER', '10.0.26100.0')

VSWHERE = os.path.join(
    os.environ.get('ProgramFiles(x86)', r'C:\Program Files (x86)'),
    'Microsoft Visual Studio', 'Installer', 'vswhere.exe')

VS_FALLBACK = os.environ.get(
    'UGMATH_MSVC_DIR',
    r'C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC')
KITS_FALLBACK = os.environ.get(
    'UGMATH_SDK_DIR',
    r'C:\Program Files (x86)\Windows Kits\10')
TS_DIRS = {'14.29': '14.29.30133', '14.30': '14.30.30705', '14.44': '14.44.35207'}

_cache = {}


def _run(cmd):
    return subprocess.run(cmd, capture_output=True, text=True, errors='replace')


def _env_ready(env):
    if not env.get('INCLUDE') or not env.get('LIB'):
        return False
    return shutil.which('cl', path=env.get('PATH', '')) is not None


def _find_vcvars():
    explicit = os.environ.get('UGMATH_VCVARS')
    if explicit:
        if os.path.isfile(explicit):
            return explicit
        raise RuntimeError('UGMATH_VCVARS 指向的文件不存在: %s' % explicit)
    if os.path.isfile(VSWHERE):
        p = _run([VSWHERE, '-latest', '-products', '*', '-requires',
                  'Microsoft.VisualStudio.Component.VC.Tools.x86.x64',
                  '-property', 'installationPath'])
        lines = [l.strip() for l in (p.stdout or '').splitlines() if l.strip()]
        for line in reversed(lines):
            cand = os.path.join(line, 'VC', 'Auxiliary', 'Build', 'vcvars64.bat')
            if os.path.isfile(cand):
                return cand
    return None


def _from_vcvars(vcvars, msvc_ver):
    cmd = 'cmd /c ""%s" -vcvars_ver=%s >nul 2>&1 && set"' % (vcvars, msvc_ver)
    p = _run(cmd)
    env = dict(os.environ)
    for line in (p.stdout or '').splitlines():
        if '=' in line:
            k, v = line.split('=', 1)
            env[k] = v
    if not _env_ready(env):
        raise RuntimeError('vcvars 未提供可用的编译环境: %s' % cmd)
    return env


def _fallback(msvc_ver):
    v = os.path.join(VS_FALLBACK, TS_DIRS.get(msvc_ver, TS_DIRS['14.29']))
    if not os.path.isfile(os.path.join(v, 'bin', 'Hostx64', 'x64', 'cl.exe')):
        raise RuntimeError('未找到 MSVC %s，请通过 UGMATH_VCVARS 指定 vcvars64.bat' % msvc_ver)
    env = dict(os.environ)
    env['PATH'] = os.path.join(v, 'bin', 'Hostx64', 'x64') + ';' + env.get('PATH', '')
    inc = [os.path.join(v, 'include'),
           os.path.join(KITS_FALLBACK, 'Include', KITS_VER, 'ucrt'),
           os.path.join(KITS_FALLBACK, 'Include', KITS_VER, 'shared'),
           os.path.join(KITS_FALLBACK, 'Include', KITS_VER, 'um'),
           os.path.join(KITS_FALLBACK, 'Include', KITS_VER, 'winrt')]
    env['INCLUDE'] = ';'.join(inc)
    lib = [os.path.join(v, 'lib', 'x64'),
           os.path.join(KITS_FALLBACK, 'Lib', KITS_VER, 'ucrt', 'x64'),
           os.path.join(KITS_FALLBACK, 'Lib', KITS_VER, 'um', 'x64')]
    env['LIB'] = ';'.join(lib)
    env['VCToolsInstallDir'] = v + os.sep
    return env


def get_env(msvc_ver=None):
    msvc_ver = msvc_ver or DEFAULT_MSVC_VER
    if msvc_ver in _cache:
        return _cache[msvc_ver]
    if _env_ready(os.environ):
        env = dict(os.environ)
    else:
        vcvars = _find_vcvars()
        if vcvars:
            try:
                env = _from_vcvars(vcvars, msvc_ver)
            except RuntimeError:
                env = _fallback(msvc_ver)
        else:
            env = _fallback(msvc_ver)
    _cache[msvc_ver] = env
    return env


def tool(name, msvc_ver=None):
    env = get_env(msvc_ver)
    p = shutil.which(name, path=env.get('PATH', ''))
    if p:
        return p
    vct = env.get('VCToolsInstallDir')
    if vct:
        cand = os.path.join(vct, 'bin', 'Hostx64', 'x64', name)
        if os.path.isfile(cand):
            return cand
    raise RuntimeError('未找到工具: %s' % name)
