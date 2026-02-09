#!/usr/bin/env python3
# Скрипт: вставляет короткие однострочные комментарии перед определениями функций/методов
# Открывает файлы в кодировке CP1251 и записывает обратно в CP1251

import re
import sys
from pathlib import Path

# mapping from keywords to short Russian action phrases
MAP = [
    (['print','show','view','display'],'выводим'),
    (['load'],'загружаем из файла'),
    (['save','write'],'сохраняем в файл'),
    (['init','initialize','setup'],'инициализируем'),
    (['getkey','getKey','getint','getInt','get'],'получаем'),
    (['set'],'устанавливаем'),
    (['sort'],'сортируем'),
    (['filter','select','copy_if','filter_'],'фильтруем'),
    (['count'],'считаем'),
    (['sum','accumulate'],'суммируем'),
    (['move','partition','swap'],'перемещаем элементы'),
    (['cls','clear'],'очищаем экран'),
    (['menu'],'формируем меню'),
    (['main'],'точка входа'),
    (['operator'],'перегружаем оператор')
]

def choose_comment(fname, func_name):
    ln = func_name.lower()
    for keys, phrase in MAP:
        for k in keys:
            if k in ln:
                return phrase
    return 'выполняем действие'

# regex to detect function/method implementation starts
func_re = re.compile(r'^\s*[\w:\<\>\s\*&~]+\s+([A-Za-z_]\w*(?:::[A-Za-z_]\w*)?)\s*\([^;]*\)\s*(?:const)?\s*\{\s*$')
# also match definitions where '{' is on same line after ) e.g. ") {"
func_re2 = re.compile(r'^\s*[\w:\<\>\s\*&~]+\s+([A-Za-z_]\w*(?:::[A-Za-z_]\w*)?)\s*\([^;]*\)\s*(?:const)?\s*\{')

EXTS = ['.cpp', '.h']

root = Path('.').resolve()
files = [p for p in root.rglob('*') if p.suffix.lower() in EXTS and '/.git/' not in str(p) and 'backups' not in str(p)]

for p in files:
    try:
        txt = p.read_text(encoding='cp1251')
    except Exception:
        # try utf-8 fallback
        try:
            txt = p.read_text(encoding='utf-8')
        except Exception:
            print('skip (encoding):', p)
            continue

    lines = txt.splitlines()
    out = []
    i = 0
    changed = False
    while i < len(lines):
        line = lines[i]
        m = func_re2.match(line)
        if not m:
            # check if signature spans multiple lines: accumulate until line containing '{'
            if ')' in line and '{' in line:
                m = None
            else:
                # try to see if this line ends a signature spanning previous lines
                # look ahead up to 3 lines to find '{'
                sig = line
                j = i
                found = False
                while j < min(len(lines), i+4):
                    if '{' in lines[j]:
                        sig = '\n'.join(lines[i:j+1])
                        if func_re.search(sig.splitlines()[-1]):
                            found = True
                        break
                    j += 1
                if found:
                    # treat as function start at i..j
                    # extract func name naive
                    allsig = '\n'.join(lines[i:j+1])
                    m2 = re.search(r'([A-Za-z_]\w*(?:::[A-Za-z_]\w*)?)\s*\(', allsig)
                    funcname = m2.group(1) if m2 else 'func'
                    comment = choose_comment(str(p), funcname)
                    out.append('// ' + comment)
                    changed = True
                    # append block
                    for k in range(i, j+1):
                        out.append(lines[k])
                    i = j+1
                    continue
        if m:
            funcname = m.group(1)
            comment = choose_comment(str(p), funcname)
            # check previous non-empty line isn't already similar comment
            prev = len(out)-1
            already = False
            while prev >= 0 and out[prev].strip() == '':
                prev -= 1
            if prev >= 0 and out[prev].strip().startswith('//'):
                # don't duplicate
                already = True
            if not already:
                out.append('// ' + comment)
                changed = True
            out.append(line)
            i += 1
            continue
        out.append(line)
        i += 1

    if changed:
        try:
            p.write_text('\n'.join(out) + '\n', encoding='cp1251')
            print('updated:', p)
        except Exception as e:
            print('write failed:', p, e)

print('Done')
