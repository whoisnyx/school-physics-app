#!/usr/bin/env python3
"""Generate compile_commands.json from Bazel aquery CppCompile actions."""
import json
import os
import subprocess
import sys

EXTERNAL_PREFIX = "external/"
BAZEL_OUT_PREFIX = "bazel-out/"
# Flag prefixes whose value may be joined onto the flag (e.g. -Iexternal/...).
PATH_FLAG_PREFIXES = ("-I", "-iquote", "-isystem", "-idirafter", "-include")
# GCC-only / output flags that clangd cannot use or would report as unknown.
SKIP_FLAGS = {
    "-fno-canonical-system-headers",
    "-fPIC",
    "-o",
}
SKIP_FLAG_PREFIXES = ("-frandom-seed=",)
SKIP_NEXT_VALUE_FLAGS = {"-MD", "-MF", "-MT", "-MQ", "-o"}


def should_skip(arg, args, idx):
    if arg in SKIP_FLAGS:
        return True
    for prefix in SKIP_FLAG_PREFIXES:
        if arg.startswith(prefix):
            return True
    if arg == "-o" and idx + 1 < len(args):
        return True
    return False


def bazel_info(name):
    result = subprocess.run(
        ["bazel", "info", name],
        capture_output=True,
        text=True,
    )
    if result.returncode != 0:
        sys.exit(f"bazel info {name} failed: {result.stderr}")
    return result.stdout.strip()


def rewrite_paths(args, execroot, output_base):
    """Rewrite execroot-relative paths into absolute ones clangd can resolve.

    In Bazel 9 the execroot no longer symlinks external repositories, so
    '-iquote external/...' would not resolve from the execroot directory.
    'external/...' lives under the output_base, 'bazel-out/...' under execroot.
    """
    rewritten = []
    skip_next = False
    for idx, arg in enumerate(args):
        if skip_next:
            skip_next = False
            continue
        if arg in SKIP_NEXT_VALUE_FLAGS:
            skip_next = True
            continue
        if should_skip(arg, args, idx):
            continue
        if arg.startswith(EXTERNAL_PREFIX):
            arg = os.path.join(output_base, arg)
        elif arg.startswith(BAZEL_OUT_PREFIX):
            arg = os.path.join(execroot, arg)
        else:
            for prefix in PATH_FLAG_PREFIXES:
                if not arg.startswith(prefix):
                    continue
                value = arg[len(prefix):]
                if value.startswith(EXTERNAL_PREFIX):
                    arg = prefix + os.path.join(output_base, value)
                elif value.startswith(BAZEL_OUT_PREFIX):
                    arg = prefix + os.path.join(execroot, value)
                break
        rewritten.append(arg)
    return rewritten


def main():
    targets = sys.argv[1:]
    if not targets:
        targets = ["//..."]

    expr = " + ".join(targets)
    result = subprocess.run(
        [
            "bazel",
            "aquery",
            "--output=jsonproto",
            f'mnemonic("CppCompile", {expr})',
        ],
        capture_output=True,
        text=True,
    )

    if result.returncode != 0:
        print(result.stderr, file=sys.stderr)
        sys.exit(1)

    execroot = bazel_info("execution_root")
    output_base = bazel_info("output_base")

    data = json.loads(result.stdout)
    compile_commands = []

    for action in data.get("actions", []):
        if action.get("mnemonic") != "CppCompile":
            continue

        args = action.get("arguments", [])
        if not args:
            continue

        # Find source file: look for -c flag or the last non-flag arg
        source_file = None
        for i, arg in enumerate(args):
            if arg == "-c" and i + 1 < len(args):
                source_file = args[i + 1]
                break

        if not source_file:
            continue

        # Resolve source_file relative to execroot if not absolute
        if not os.path.isabs(source_file):
            source_file = os.path.join(execroot, source_file)

        # Bazel stores sources as symlinks into the execroot. clangd matches
        # compile_commands.json entries by the real file path of the opened
        # document, so resolve the symlink to the actual source in the repo.
        source_file = os.path.realpath(source_file)

        args = rewrite_paths(args, execroot, output_base)

        compile_commands.append({
            "directory": execroot,
            "file": source_file,
            "arguments": args,
        })

    print(json.dumps(compile_commands, indent=2))


if __name__ == "__main__":
    main()