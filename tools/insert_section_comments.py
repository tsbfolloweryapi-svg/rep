#!/usr/bin/env python3
# Вставляет секционные однострочные заголовки перед реализациями функций/методов
# Исключает файлы: Utils, Colors, Palette, Menu, MenuItem, FKeys

import re
from pathlib import Path

EXCLUDE_NAMES = ['Utils', 'Colors', 'Palette', 'Menu', 'MenuItem', 'FKeys']
EXTS = ['.cpp', '.h']

# mapping: keyword -> section header
SECTIONS = [
    (['sort', 'sortby', 'sort_'], 'Сортировка'),
    (['load', 'save', 'read', 'write', 'binary', 'file', 'stream', 'readFrom', 'writeTo'], 'Работа с файлом'),
    (['view', 'print', 'show', 'display', 'paint'], 'Вывод/Отображение'),
    (['init', 'setup', 'ctor', 'App::App', 'main'], 'Инициализация/Точка входа'),
    (['filter', 'select', 'copy_if', 'find', 'remove_if'], 'Фильтрация/Выборка'),
    (['count', 'sum', 'accumulate', 'total'], 'Подсчёт/Агрегация'),
    (['move', 'swap', 'partition', 'shift'], 'Перемещение/Трансформация'),
    (['menu', 'command', 'cmd', 'handle'], 'Обработка команд/меню'),
    (['request', 'request', 'handle', 'process'], 'Обработка/Запросы')
]

# regex to detect function/method implementation starts (simple heuristic)
FUNC_RE = re.compile(r'^\s*([\w:\<\>~\*&\s]+)\s+([A-Za-z_]\w*(?:::[A-Za-z_]\w*)?)\s*\([^;]*\)\s*(?:const)?\s*\{\s*$')
FUNC_RE_INLINE = re.compile(r'([A-Za-z_]\w*(?:::[A-Za-z_]\w*)?)\s*\(')

root = Path('.').resolve()
files = [p for p in root.rglob('*') if p.suffix in EXTS]

for p in files:
    name = p.stem
    # skip excluded names
    if any(ex in str(p) for ex in EXCLUDE_NAMES):
        continue
    # also skip tools folder
    if 'tools' in str(p.parts):
        continue

    try:
        txt = p.read_text(encoding='utf-8')
    except Exception:
        try:
            txt = p.read_text(encoding='cp1251')
        except Exception:
            print('skip (encoding):', p)
            continue

    lines = txt.splitlines()
    out = []
    changed = False
    i = 0
    while i < len(lines):
        line = lines[i]
        m = FUNC_RE.match(line)
        if m:
            ret = m.group(1)
            funcname = m.group(2)
            # decide section
            section = None
            ln = funcname.lower()
            for keys, sect in SECTIONS:
                for k in keys:
                    if k.lower() in ln or k.lower() in ret.lower():
                        section = sect
                        break
                if section:
                    break
            if not section:
                # fallback: inspect following 3 lines for keywords
                block = '\n'.join(lines[i:i+4]).lower()
                for keys, sect in SECTIONS:
                    for k in keys:
                        if k.lower() in block:
                            section = sect
                            break
                    if section:
                        break
            if not section:
                section = 'Блок'  # generic

            # ensure not duplicating similar comment directly above
            prev = len(out)-1
            already = False
            while prev >= 0 and out[prev].strip() == '':
                prev -= 1
            if prev >= 0 and out[prev].strip().startswith('//') and section in out[prev]:
                already = True

            if not already:
                out.append('// ' + section)
                changed = True
            out.append(line)
            i += 1
            continue
        # also try multi-line signatures where '{' is on next line
        if line.strip().endswith(')') or line.strip().endswith(') const'):
            # lookahead for '{'
            j = i+1
            found = False
            while j < min(len(lines), i+3):
                if '{' in lines[j]:
                    sig = '\n'.join(lines[i:j+1])
                    mm = FUNC_RE_INLINE.search(sig)
                    if mm:
                        funcname = mm.group(1)
                        # decide section same as above
                        section = None
                        ln = funcname.lower()
                        for keys, sect in SECTIONS:
                            for k in keys:
                                if k.lower() in ln:
                                    section = sect
                                    break
                            if section:
                                break
                        if not section:
                            section = 'Блок'

                        prev = len(out)-1
                        already = False
                        while prev >= 0 and out[prev].strip() == '':
                            prev -= 1
                        if prev >= 0 and out[prev].strip().startswith('//') and section in out[prev]:
                            already = True

                        if not already:
                            out.append('// ' + section)
                            changed = True
                        # append lines i..j
                        for k in range(i, j+1):
                            out.append(lines[k])
                        i = j+1
                        found = True
                        break
                j += 1
            if found:
                continue
        out.append(line)
        i += 1

    if changed:
        try:
            p.write_text('\n'.join(out) + '\n', encoding='utf-8')
            print('updated:', p)
        except Exception as e:
            print('write failed:', p, e)

print('Done')
