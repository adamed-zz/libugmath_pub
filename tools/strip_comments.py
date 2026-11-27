#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""注释剥离工具（按词法，保护字符串/字符字面量）。

用法:
  python -I strip_comments.py check  <root|file>...
  python -I strip_comments.py strip  <root|file>... [--dry-run] [--verbose]
  python -I strip_comments.py clean  <root|file>...        # 断言已无注释（幂等）
  python -I strip_comments.py verify <orig_root> <new_root>  # 对比字符串字面量序列

处理规则:
  - C/C++ (.cpp/.c/.h/.hpp/...): 删除 // 与 /* */，保护普通字符串、字符字面量、
    原始字符串 R"delim(...)delim"、数字分隔符（1'000）、行尾反斜杠续行。
  - Python (.py): 基于 tokenize 删除 # 注释（保留 docstring）。
  - 汇编/链接脚本 (.asm/.def): 删除引号外的 ; 注释。
  - 注释替换为单个空格并保留全部换行（行号不变），删注释行的行尾空白会被清理。
"""
import io
import os
import sys
import tokenize

CPP_EXT = {'.cpp', '.c', '.cc', '.cxx', '.h', '.hpp', '.hh', '.hxx', '.inl'}
ASM_EXT = {'.asm', '.def'}
PY_EXT = {'.py'}
ALL_EXT = CPP_EXT | ASM_EXT | PY_EXT


# ---------------------------------------------------------------- 通用工具

def iter_code_files(root):
    if os.path.isfile(root):
        if os.path.splitext(root)[1].lower() in ALL_EXT:
            yield root
        return
    for dirpath, dirnames, filenames in os.walk(root):
        dirnames[:] = sorted(d for d in dirnames if d != '.git')
        for fn in sorted(filenames):
            if os.path.splitext(fn)[1].lower() in ALL_EXT:
                yield os.path.join(dirpath, fn)


def _split_lines_keepends(data):
    """仅按 \\n 切分并保留行尾，保证与扫描器的行数完全一致。"""
    lines = []
    start = 0
    n = len(data)
    while start < n:
        k = data.find(b'\n', start)
        if k < 0:
            lines.append(data[start:])
            break
        lines.append(data[start:k + 1])
        start = k + 1
    return lines


def _rstrip_line_bytes(line):
    for term in (b'\r\n', b'\n', b'\r'):
        if line.endswith(term):
            body = line[:-len(term)]
            return body.rstrip(b' \t') + term
    return line.rstrip(b' \t')


def _rstrip_line_str(line):
    for term in ('\r\n', '\n', '\r'):
        if line.endswith(term):
            body = line[:-len(term)]
            return body.rstrip(' \t') + term
    return line.rstrip(' \t')


def _postpass_rstrip(orig, new):
    """对内容发生变化的行（即删过注释的行）清理行尾空白；行数必须一致。"""
    o = _split_lines_keepends(orig)
    nw = _split_lines_keepends(new)
    if len(o) != len(nw):
        return new, False
    changed = False
    for k in range(len(nw)):
        if o[k] != nw[k]:
            r = _rstrip_line_bytes(nw[k])
            if r != nw[k]:
                nw[k] = r
                changed = True
    if not changed:
        return new, True
    return b''.join(nw), True


def _is_ident_byte(b):
    return ((0x30 <= b <= 0x39) or (0x41 <= b <= 0x5a)
            or (0x61 <= b <= 0x7a) or b == 0x5f)


def _is_digit_sep(data, i):
    """data[i] == '\'' 且处于 1'000 形式的数字分隔符位置。"""
    if i <= 0 or i + 1 >= len(data):
        return False
    prev = data[i - 1]
    if not (0x30 <= prev <= 0x39):
        return False
    nxt = data[i + 1]
    return (0x30 <= nxt <= 0x39) or (0x41 <= nxt <= 0x46) or (0x61 <= nxt <= 0x66)


# ---------------------------------------------------------------- C/C++

def _raw_string_end(data, i):
    """data[i:i+2] == b'R"'。返回原始字符串结束位置（含结尾引号）；不是合法起始返回 None。"""
    n = len(data)
    j = i + 2
    k = j
    while k < n and k - j <= 16:
        c = data[k]
        if c == 0x28:  # '('
            delim = data[j:k]
            term = b')' + delim + b'"'
            p = data.find(term, k + 1)
            return n if p < 0 else p + len(term)
        if c in b' \t\r\n\\)("':
            return None
        k += 1
    return None


def _is_raw_string_start(data, i):
    n = len(data)
    if data[i:i + 2] != b'R"':
        return False
    if i == 0 or not _is_ident_byte(data[i - 1]):
        return _raw_string_end(data, i) is not None
    for pre in (b'u8', b'u', b'U', b'L'):
        if i >= len(pre) and data[i - len(pre):i] == pre:
            if i - len(pre) == 0 or not _is_ident_byte(data[i - len(pre) - 1]):
                return _raw_string_end(data, i) is not None
    return False


def strip_cpp(data):
    """返回 (新内容, 统计, 警告列表)。"""
    n = len(data)
    out = bytearray()
    i = 0
    stats = {'line_comments': 0, 'block_comments': 0}
    warnings = []

    def line_no(pos):
        return data.count(b'\n', 0, pos) + 1

    if data[:3] == b'\xef\xbb\xbf':
        out += data[:3]
        i = 3
    while i < n:
        c = data[i]
        # // 行注释
        if c == 0x2f and i + 1 < n and data[i + 1] == 0x2f:
            stats['line_comments'] += 1
            i += 2
            while i < n:
                c2 = data[i]
                if c2 == 0x0a or c2 == 0x0d:
                    break
                if c2 == 0x5c:  # 行尾续行符让注释延续到下一行
                    if i + 1 < n and data[i + 1] == 0x0a:
                        out += b'\n'
                        i += 2
                        continue
                    if i + 2 < n and data[i + 1] == 0x0d and data[i + 2] == 0x0a:
                        out += b'\r\n'
                        i += 3
                        continue
                i += 1
            out += b' '
            continue
        # /* */ 块注释
        if c == 0x2f and i + 1 < n and data[i + 1] == 0x2a:
            stats['block_comments'] += 1
            i += 2
            out += b' '
            terminated = False
            while i < n:
                c2 = data[i]
                if c2 == 0x2a and i + 1 < n and data[i + 1] == 0x2f:
                    i += 2
                    terminated = True
                    break
                if c2 == 0x0d and i + 1 < n and data[i + 1] == 0x0a:
                    out += b'\r\n'
                    i += 2
                elif c2 in (0x0a, 0x0d):
                    out += data[i:i + 1]
                    i += 1
                else:
                    i += 1
            if not terminated:
                warnings.append('block comment unterminated at line %d' % line_no(i))
            continue
        # 原始字符串 R"delim(...)delim"
        if c == 0x52 and i + 1 < n and data[i + 1] == 0x22 and _is_raw_string_start(data, i):
            end = _raw_string_end(data, i)
            if end is None:
                end = i + 1
            out += data[i:end]
            i = end
            continue
        # 普通字符串
        if c == 0x22:
            out += data[i:i + 1]
            i += 1
            terminated = False
            while i < n:
                c2 = data[i]
                if c2 == 0x5c and i + 1 < n:  # 反斜杠转义（含 \ 换行 的续行）
                    if i + 2 < n and data[i + 1] == 0x0d and data[i + 2] == 0x0a:
                        out += data[i:i + 3]
                        i += 3
                    else:
                        out += data[i:i + 2]
                        i += 2
                    continue
                out += data[i:i + 1]
                i += 1
                if c2 == 0x22:
                    terminated = True
                    break
                if c2 in (0x0a, 0x0d):
                    break
            if not terminated:
                warnings.append('string literal unterminated near line %d' % line_no(i))
            continue
        # 字符字面量（排除数字分隔符）
        if c == 0x27:
            if _is_digit_sep(data, i):
                out += data[i:i + 1]
                i += 1
                continue
            out += data[i:i + 1]
            i += 1
            terminated = False
            while i < n:
                c2 = data[i]
                if c2 == 0x5c and i + 1 < n:
                    if i + 2 < n and data[i + 1] == 0x0d and data[i + 2] == 0x0a:
                        out += data[i:i + 3]
                        i += 3
                    else:
                        out += data[i:i + 2]
                        i += 2
                    continue
                out += data[i:i + 1]
                i += 1
                if c2 == 0x27:
                    terminated = True
                    break
                if c2 in (0x0a, 0x0d):
                    break
            if not terminated:
                warnings.append('char literal unterminated near line %d' % line_no(i))
            continue
        out += data[i:i + 1]
        i += 1
    new, ok = _postpass_rstrip(data, bytes(out))
    if not ok:
        warnings.append('line count mismatch after strip')
    stats['removed_bytes'] = len(data) - len(new)
    return new, stats, warnings


def extract_cpp_literals(data):
    """提取字符串/字符字面量文本（含定界符），用于剥后对比。"""
    lits = []
    n = len(data)
    i = 0
    while i < n:
        c = data[i]
        if c == 0x2f and i + 1 < n and data[i + 1] == 0x2f:
            i += 2
            while i < n:
                c2 = data[i]
                if c2 in (0x0a, 0x0d):
                    break
                if c2 == 0x5c and i + 1 < n and data[i + 1] == 0x0a:
                    i += 2
                    continue
                i += 1
            continue
        if c == 0x2f and i + 1 < n and data[i + 1] == 0x2a:
            i += 2
            while i < n:
                if data[i] == 0x2a and i + 1 < n and data[i + 1] == 0x2f:
                    i += 2
                    break
                i += 1
            continue
        if c == 0x52 and i + 1 < n and data[i + 1] == 0x22 and _is_raw_string_start(data, i):
            end = _raw_string_end(data, i)
            if end is None:
                end = i + 1
            lits.append(data[i:end])
            i = end
            continue
        if c == 0x22:
            start = i
            i += 1
            while i < n:
                c2 = data[i]
                if c2 == 0x5c and i + 1 < n:
                    if i + 2 < n and data[i + 1] == 0x0d and data[i + 2] == 0x0a:
                        i += 3
                    else:
                        i += 2
                    continue
                i += 1
                if c2 == 0x22:
                    break
                if c2 in (0x0a, 0x0d):
                    break
            lits.append(data[start:i])
            continue
        if c == 0x27 and not _is_digit_sep(data, i):
            start = i
            i += 1
            while i < n:
                c2 = data[i]
                if c2 == 0x5c and i + 1 < n:
                    if i + 2 < n and data[i + 1] == 0x0d and data[i + 2] == 0x0a:
                        i += 3
                    else:
                        i += 2
                    continue
                i += 1
                if c2 == 0x27:
                    break
                if c2 in (0x0a, 0x0d):
                    break
            lits.append(data[start:i])
            continue
        i += 1
    return lits


# ---------------------------------------------------------------- Python

def strip_py(data):
    stats = {'comments': 0}
    warnings = []
    bom = data.startswith(b'\xef\xbb\xbf')
    raw = data[3:] if bom else data
    try:
        text = raw.decode('utf-8')
    except UnicodeDecodeError as e:
        return None, stats, ['not utf-8: %s' % e]
    lines = text.splitlines(keepends=True)
    spans = []
    try:
        for tok in tokenize.generate_tokens(io.StringIO(text).readline):
            if tok.type == tokenize.COMMENT:
                spans.append((tok.start[0] - 1, tok.start[1], tok.end[1]))
    except (tokenize.TokenError, SyntaxError, IndentationError) as e:
        return None, stats, ['tokenize failed: %s' % e]
    stats['comments'] = len(spans)
    dirty = set()
    for idx, c0, c1 in spans:
        lines[idx] = lines[idx][:c0] + lines[idx][c1:]
        dirty.add(idx)
    for idx in dirty:
        lines[idx] = _rstrip_line_str(lines[idx])
    out = ''.join(lines).encode('utf-8')
    if bom:
        out = b'\xef\xbb\xbf' + out
    stats['removed_bytes'] = len(data) - len(out)
    return out, stats, warnings


def extract_py_literals(data):
    bom = data.startswith(b'\xef\xbb\xbf')
    raw = data[3:] if bom else data
    text = raw.decode('utf-8')
    lits = []
    try:
        for tok in tokenize.generate_tokens(io.StringIO(text).readline):
            if tok.type == tokenize.STRING or getattr(tokenize, 'FSTRING_START', None) == tok.type:
                lits.append(tok.string)
    except (tokenize.TokenError, SyntaxError, IndentationError):
        return None
    return lits


# ---------------------------------------------------------------- ASM / DEF

def strip_asm(data):
    stats = {'comments': 0}
    warnings = []
    n = len(data)
    out = bytearray()
    i = 0

    def line_no(pos):
        return data.count(b'\n', 0, pos) + 1

    while i < n:
        c = data[i]
        if c == 0x3b:  # ';'
            stats['comments'] += 1
            while i < n and data[i] not in (0x0a, 0x0d):
                i += 1
            continue
        if c in (0x22, 0x27):  # 引号字符串
            q = c
            out += data[i:i + 1]
            i += 1
            terminated = False
            while i < n:
                c2 = data[i]
                out += data[i:i + 1]
                i += 1
                if c2 == q:
                    if i < n and data[i] == q:  # MASM 成对引号转义
                        out += data[i:i + 1]
                        i += 1
                        continue
                    terminated = True
                    break
                if c2 in (0x0a, 0x0d):
                    break
            if not terminated:
                warnings.append('quoted string unterminated near line %d' % line_no(i))
            continue
        out += data[i:i + 1]
        i += 1
    new, ok = _postpass_rstrip(data, bytes(out))
    if not ok:
        warnings.append('line count mismatch after strip')
    stats['removed_bytes'] = len(data) - len(new)
    return new, stats, warnings


def extract_asm_literals(data):
    lits = []
    n = len(data)
    i = 0
    while i < n:
        c = data[i]
        if c == 0x3b:
            while i < n and data[i] not in (0x0a, 0x0d):
                i += 1
            continue
        if c in (0x22, 0x27):
            q = c
            start = i
            i += 1
            while i < n:
                c2 = data[i]
                i += 1
                if c2 == q:
                    if i < n and data[i] == q:
                        i += 1
                        continue
                    break
                if c2 in (0x0a, 0x0d):
                    break
            lits.append(data[start:i])
            continue
        i += 1
    return lits


# ---------------------------------------------------------------- 分发

def strip_file(path):
    with open(path, 'rb') as f:
        data = f.read()
    ext = os.path.splitext(path)[1].lower()
    if ext in CPP_EXT:
        new, stats, warns = strip_cpp(data)
    elif ext in PY_EXT:
        new, stats, warns = strip_py(data)
    else:
        new, stats, warns = strip_asm(data)
    return data, new, stats, warns


def walk_pairs(orig_root, new_root):
    for p in iter_code_files(orig_root):
        rel = os.path.relpath(p, orig_root)
        q = os.path.join(new_root, rel)
        if os.path.isfile(q):
            yield p, q


def main(argv):
    if len(argv) < 3 or argv[1] not in ('check', 'strip', 'clean', 'verify'):
        print(__doc__)
        return 2
    mode = argv[1]
    if mode == 'verify':
        orig_root, new_root = argv[2], argv[3]
        bad = 0
        files = 0
        missing = 0
        for p, q in walk_pairs(orig_root, new_root):
            if not os.path.isfile(q):
                missing += 1
                print('MISSING IN NEW TREE: %s' % p)
                continue
            files += 1
            ext = os.path.splitext(p)[1].lower()
            with open(p, 'rb') as f:
                a = f.read()
            with open(q, 'rb') as f:
                b = f.read()
            if ext in CPP_EXT:
                la = extract_cpp_literals(a)
                lb = extract_cpp_literals(b)
            elif ext in PY_EXT:
                la = extract_py_literals(a)
                lb = extract_py_literals(b)
            else:
                la = extract_asm_literals(a)
                lb = extract_asm_literals(b)
            if la is None or lb is None or la != lb:
                bad += 1
                print('LITERAL MISMATCH: %s' % p)
                if la is not None and lb is not None:
                    for x, y in zip(la, lb):
                        if x != y:
                            print('  orig: %r' % x[:120])
                            print('  new : %r' % y[:120])
                            break
                    if len(la) != len(lb):
                        print('  count %d -> %d' % (len(la), len(lb)))
        print('verify: %d files, %d mismatches, %d missing' % (files, bad, missing))
        return 1 if (bad or missing) else 0
    dry = '--dry-run' in argv
    verbose = '--verbose' in argv
    roots = [a for a in argv[2:] if not a.startswith('--')]
    total_files = 0
    changed_files = 0
    total_removed = 0
    all_warns = []
    for root in roots:
        for path in iter_code_files(root):
            total_files += 1
            data, new, stats, warns = strip_file(path)
            if new is None:
                all_warns.append((path, warns))
                continue
            if warns:
                all_warns.append((path, warns))
            if new != data:
                changed_files += 1
                total_removed += stats.get('removed_bytes', 0)
                if verbose:
                    print('CHANGED %s (removed %d B)' % (path, stats.get('removed_bytes', 0)))
                if mode == 'strip' and not dry:
                    with open(path, 'wb') as f:
                        f.write(new)
    if mode == 'clean':
        remaining = [p for p, w in all_warns]
        print('clean: %d files, %d still-with-comments/errors' % (total_files, changed_files))
        for p in remaining[:50]:
            print('  ', p)
        return 1 if changed_files else 0
    print('%s: %d files, %d changed (dry=%s), %d bytes removed'
          % (mode, total_files, changed_files, dry, total_removed))
    if all_warns:
        print('warnings on %d files:' % len(all_warns))
        for p, ws in all_warns[:100]:
            print('  %s: %s' % (p, '; '.join(ws)))
    return 0


if __name__ == '__main__':
    sys.exit(main(sys.argv))
