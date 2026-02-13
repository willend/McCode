#!/usr/bin/env python3
"""
mccode-clangformat.py

Traverse a McCode checkout, find .instr and .comp files, reformat C-like code
only inside %{  %} sections to a recommended clang-style indentation, keeping
delimiters on their own lines and treating block contents as first-level code
(i.e., add one extra indent level inside the block).

Usage:
    python mccode-clangformat.py [--repo PATH] [--clang-format PATH] [--check]
"""
import argparse
import os
import re
import shutil
import subprocess
import sys
from pathlib import Path
from typing import List, Tuple

# ---- Config ----
FILE_EXTS = ('.instr', '.comp')
BACKUP_SUFFIX = '.orig'
INDENT_WIDTH = 4
CLANG_STYLE = """
BasedOnStyle: Google
IndentWidth: 4
UseTab: Never
BreakBeforeBraces: Attach
ColumnLimit: 80
DerivePointerAlignment: false
PointerAlignment: Left
"""

# Match a %{ on its own line then capture inner until a %} on its own line.
BLOCK_RE = re.compile(r'(^[ \t]*%\{\s*\n)(.*?)(\n[ \t]*%\}[ \t]*$)', re.DOTALL | re.MULTILINE)

def find_files(root: Path) -> List[Path]:
    files = []
    for dirpath, _, filenames in os.walk(root):
        for fn in filenames:
            if fn.endswith(FILE_EXTS):
                files.append(Path(dirpath) / fn)
    return files

def simple_reindent_c(code: str, indent_width: int = INDENT_WIDTH) -> str:
    out_lines = []
    indent_level = 0
    in_block_comment = False
    for line in code.splitlines():
        raw = line.rstrip('\n')
        stripped = raw.lstrip()
        if stripped == '':
            out_lines.append('')
            continue

        n = len(raw)
        first_nonspace = None
        for idx,ch in enumerate(raw):
            if not ch.isspace():
                first_nonspace = idx
                break

        j = 0
        local_in_block_comment = in_block_comment
        reduce_before = 0
        increase_after = 0
        state_in_string = False
        string_char = ''
        escape = False
        while j < n:
            ch = raw[j]
            if local_in_block_comment:
                if raw.startswith('*/', j):
                    local_in_block_comment = False
                    j += 2
                    continue
                j += 1
                continue
            if raw.startswith('//', j):
                break
            if raw.startswith('/*', j):
                local_in_block_comment = True
                j += 2
                continue
            if state_in_string:
                if escape:
                    escape = False
                elif ch == '\\':
                    escape = True
                elif ch == string_char:
                    state_in_string = False
                    string_char = ''
                j += 1
                continue
            else:
                if ch == '"' or ch == "'":
                    state_in_string = True
                    string_char = ch
                    j += 1
                    continue
                if ch == '}':
                    if first_nonspace is not None and j == first_nonspace:
                        reduce_before += 1
                    else:
                        reduce_before += 1
                    j += 1
                    continue
                if ch == '{':
                    increase_after += 1
                    j += 1
                    continue
                j += 1

        use_level = max(indent_level - reduce_before, 0)
        new_leading = ' ' * (use_level * indent_width)
        out_lines.append(new_leading + stripped)
        indent_level = use_level + increase_after
        in_block_comment = local_in_block_comment

    if code.endswith('\n'):
        return '\n'.join(out_lines) + '\n'
    else:
        return '\n'.join(out_lines)

def run_clang_format(code: str, clang_path: str) -> str:
    p = subprocess.Popen([clang_path, '-style', CLANG_STYLE], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    out, err = p.communicate(code)
    if p.returncode != 0:
        raise RuntimeError(f'clang-format failed: {err.strip()}')
    return out

def add_extra_indent(formatted: str, extra_indent: int = INDENT_WIDTH) -> str:
    """
    Add extra_indent spaces to each non-blank line of formatted block.
    Preserve blank lines as empty.
    """
    lines = formatted.splitlines()
    out = []
    prefix = ' ' * extra_indent
    for ln in lines:
        if ln.strip() == '':
            out.append('')
        else:
            out.append(prefix + ln)
    if formatted.endswith('\n'):
        return '\n'.join(out) + '\n'
    else:
        return '\n'.join(out)

def process_file(path: Path, clang_path: str = None, check_only: bool = False) -> Tuple[bool, str]:
    text = path.read_text(encoding='utf-8')
    changed = False

    def repl(m: re.Match) -> str:
        nonlocal changed
        leading = m.group(1)  # "%{" line incl newline
        inner = m.group(2)
        trailing = m.group(3)  # newline + "%}" line
        inner_for_format = inner
        try:
            if clang_path:
                formatted_inner = run_clang_format(inner_for_format, clang_path)
            else:
                formatted_inner = simple_reindent_c(inner_for_format, indent_width=INDENT_WIDTH)
        except Exception as e:
            raise RuntimeError(f'Formatting failed: {e}')
        # Strip surrounding newlines from formatted core, then add one newline boundaries so delimiters stay on own lines
        core = formatted_inner.strip('\n')
        # Apply extra indent (treat block as first-level code)
        if core == '':
            indented_core = ''
        else:
            indented_core = add_extra_indent(core + '\n', extra_indent=INDENT_WIDTH)
            # add_extra_indent returns trailing newline; remove last newline to control later
            indented_core = indented_core.rstrip('\n')
        # Build result: leading already includes '%{' and its newline; we want exactly:
        # leading + indented_core + '\n' + trailing.lstrip('\n')
        if indented_core == '':
            result = leading + '\n' + trailing.lstrip('\n')
        else:
            result = leading + indented_core + '\n' + trailing.lstrip('\n')
        if result != m.group(0):
            changed = True
        return result

    try:
        new_text = BLOCK_RE.sub(repl, text)
    except RuntimeError as e:
        return False, str(e)

    if changed:
        if check_only:
            return True, ''
        bak = path.with_suffix(path.suffix + BACKUP_SUFFIX)
        if not bak.exists():
            shutil.copy2(path, bak)
        path.write_text(new_text, encoding='utf-8')
    return changed, ''

def main():
    ap = argparse.ArgumentParser(description='Adapt indentation in McCode %{ %} blocks (delims on own lines, block is first-level).')
    ap.add_argument('--repo', '-r', default='.', help='Repo path (default: current dir)')
    ap.add_argument('--clang-format', '-c', default=None, help='Path to clang-format (optional)')
    ap.add_argument('--check', action='store_true', help="Check only; don't write files")
    args = ap.parse_args()

    root = Path(args.repo).resolve()
    if not root.exists():
        print(f'Repo path not found: {root}', file=sys.stderr)
        sys.exit(2)

    files = find_files(root)
    if not files:
        print('No .instr or .comp files found.', file=sys.stderr)
        sys.exit(1)

    any_changed = False
    failures = []
    for f in files:
        try:
            changed, msg = process_file(f, clang_path=args.clang_format, check_only=args.check)
            if msg:
                failures.append(msg)
            if changed:
                any_changed = True
                print(f'Changed: {f}')
        except Exception as e:
            failures.append(f'Error processing {f}: {e}')

    if failures:
        print('Some files had errors:', file=sys.stderr)
        for m in failures:
            print(m, file=sys.stderr)
        sys.exit(3 if not any_changed else 0)

    if any_changed:
        if args.check:
            print('Files would be changed.')
            sys.exit(0)
        print('Done.')
    else:
        print('No changes necessary.')

if __name__ == '__main__':
    main()

