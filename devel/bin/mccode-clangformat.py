#!/usr/bin/env python3
"""
mccode-clangformat.py

Traverse a McCode checkout, find .instr and .comp files, reformat C-like code
only inside %{  %} sections using clang-format with repository .clang-format
style, keeping delimiters on their own lines.

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

# Match a %{ on its own line then capture inner until a %} on its own line.
BLOCK_RE = re.compile(
    r'(^[ \t]*%[\s]*\{\s*\n)(.*?)(\n[ \t]*%\}[ \t]*$)',
    re.DOTALL | re.MULTILINE
)


def find_files(root: Path) -> List[Path]:
    files = []
    for dirpath, _, filenames in os.walk(root):
        for fn in filenames:
            if fn.endswith(FILE_EXTS):
                files.append(Path(dirpath) / fn)
    return files

def run_clang_format_file_style(code: str, clang_path: str, assume_filename: Path) -> str:
    """
    Run clang-format with -style=file so it picks up the repository .clang-format.
    """
    cmd = [clang_path, '-style', 'file', '-assume-filename', str(assume_filename)]
    p = subprocess.Popen(
        cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
        stderr=subprocess.PIPE, text=True
    )
    out, err = p.communicate(code)
    if p.returncode != 0:
        raise RuntimeError(f'clang-format failed for {assume_filename}:\n{err.strip()}')
    return out

def process_file(path: Path, clang_path: str, style_file: Path, check_only: bool = False) -> Tuple[bool, str]:
    """
    Returns (changed, err_msg).
    """
    text = path.read_text(encoding='utf-8')
    changed = False

    def repl(m: re.Match) -> str:
        nonlocal changed
        leading = m.group(1)
        inner = m.group(2)
        trailing = m.group(3)

        try:
            
            formatted_inner = run_clang_format_file_style(
                inner,
                clang_path=clang_path,
                assume_filename=style_file   # force clang-format to use the script's style file
            )

        except Exception as e:
            raise RuntimeError(f'Formatting failed for {path}: {e}')

        # Strip outer newlines, but DO NOT add extra indent anymore
        core = formatted_inner.strip('\n')

        # If clang-format produced nothing meaningful, keep empty
        if core == '':
            result = leading + "\n" + trailing.lstrip("\n")
        else:
            # Preserve delimiters on their own lines
            result = leading + core + "\n" + trailing.lstrip("\n")

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

def ensure_clang_format(clang_path_arg: str | None) -> str:
    if clang_path_arg:
        return clang_path_arg
    return 'clang-format'

def main():
    ap = argparse.ArgumentParser(
        description='Format code inside McCode %{ %} blocks using repository .clang-format'
    )
    ap.add_argument('--repo', '-r', default='.', help='Repo path (default: current dir)')
    ap.add_argument('--clang-format', '-c', default=None, help='Path to clang-format executable')
    ap.add_argument('--check', action='store_true', help="Check only; don't write files")
    args = ap.parse_args()

    root = Path(args.repo).resolve()
    if not root.exists():
        print(f'Repo path not found: {root}', file=sys.stderr)
        sys.exit(2)
    
    # Warn if no .clang-format file is found in this repo tree
    
    # Determine the directory containing this script (…/McCode/devel/)
    script_dir = Path(__file__).resolve().parent.parent
    style_file = script_dir / "clang-format"
    print(style_file)

    # Require .clang-format to exist right next to this script
    if not style_file.exists():
        print(f"ERROR: Expected .clang-format file in {script_dir}, but none was found.", file=sys.stderr)
        sys.exit(2)

    if style_file is None:
        print("WARNING: No .clang-format file found in this repository. "
            "clang-format will use its built-in default style.",
            file=sys.stderr)
    else:
        print(f"Using style file: {style_file}")


    clang_path = ensure_clang_format(args.clang_format)

    files = find_files(root)
    if not files:
        print('No .instr or .comp files found.', file=sys.stderr)
        sys.exit(1)

    any_changed = False
    failures = []

    for f in files:
        try:
            changed, msg = process_file(
                f, clang_path=clang_path, style_file=style_file, check_only=args.check
            )
            if msg:
                failures.append(msg)
            if changed:
                any_changed = True
                print(f'Changed: {f}')
        except FileNotFoundError:
            failures.append('clang-format executable not found.')
            break
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
        else:
            print('Done.')
    else:
        print('No changes necessary.')

if __name__ == '__main__':
    main()