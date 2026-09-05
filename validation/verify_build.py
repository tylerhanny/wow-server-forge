#!/usr/bin/env python3
"""Independent pinned-file warning provenance gate; candidate policy is never used."""

import argparse
import difflib
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys
import time

POLICY_PATH = Path(__file__).with_name("upstream-warning-policy.json")
FIXTURE_POLICY_PATH = Path(__file__).with_name("worldmock-fixture.json")
FIXTURE_PATCH_PATH = Path(__file__).with_name("worldmock-fixture.patch")
DEMOTION = "-Wno-error"
SOURCE_SUFFIXES = {".c", ".cc", ".cpp", ".cxx", ".h", ".hh", ".hpp", ".hxx", ".inc", ".inl", ".ipp", ".tcc"}
PHYSICAL_FLAGS = ["-Xclang", "-fno-diagnostics-use-presumed-location", "-fdiagnostics-absolute-paths",
                  "-fmacro-backtrace-limit=0", "-ftemplate-backtrace-limit=0"]
WARNING = re.compile(r"\bwarnings?\b", re.IGNORECASE)
ERROR = re.compile(r"\b(?:fatal\s+)?error\s*:|\bCMake Error\b", re.IGNORECASE)
CONTROL = re.compile(r"[\x00-\x08\x0b\x0c\x0e-\x1f\x7f]")
PROGRESS = re.compile(r"^\[\s*\d+%\]\s+(?:Building (?:C|CXX) object .+|Built target \S+|Linking .+)$")
BUILD_PROGRESS = re.compile(r"^\[\s*\d+%\]\s+Building (?:C|CXX) object (.+)$")


class GateFailure(Exception):
    pass


def require(condition, message):
    if not condition:
        raise GateFailure(message)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def load_policy(path=POLICY_PATH):
    policy = json.loads(Path(path).read_text(encoding="utf-8"))
    require(policy["schema"] == 1 and policy["upstream_warnings"] == "verified-unchanged-tracked-files-only",
            "Unsupported protected upstream warning policy")
    require(all(policy[key] == "fatal" for key in ("project_warnings", "unknown_warnings", "errors")),
            "Project/unknown warnings and errors must remain fatal")
    return policy


def git(repo, *args):
    result = subprocess.run(
        ["git", "--no-replace-objects", "-C", str(repo), *args],
        check=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        env={**os.environ, "GIT_NO_REPLACE_OBJECTS": "1"})
    require(result.returncode == 0, f"Git identity/integrity check failed: {' '.join(args)}")
    return result.stdout


def fixture_policy():
    value = json.loads(FIXTURE_POLICY_PATH.read_text(encoding="utf-8"))
    require(value["schema"] == 1 and value["path"] == "src/test/mocks/WorldMock.h",
            "Unsupported test-fixture exception")
    require(digest(FIXTURE_PATCH_PATH.read_bytes()) == value["patch_sha256"],
            "Protected WorldMock patch identity changed")
    return value


def corrected_fixture_bytes(original, fixture):
    """Pure in-memory transformation; never export the complete corrected header."""
    require(digest(original) == fixture["original_sha256"], "WorldMock original bytes changed")
    require(hashlib.sha1(b"blob " + str(len(original)).encode() + b"\0" + original).hexdigest() ==
            fixture["original_git_blob"], "WorldMock original Git blob changed")
    before = original.decode("utf-8")
    after = before
    for anchor, addition in (
        ('    MOCK_METHOD(char const *, GetDBVersion, (), (const));\n',
         '#ifdef MOD_PLAYERBOTS\n'
         '    MOCK_METHOD(char const*, GetPlayerbotsDBRevision, (), (const, override));\n'
         '#endif\n'),
        ('    MOCK_METHOD(void, SetRealmName, (std::string name), ());\n',
         '    MOCK_METHOD(SQLQueryHolderCallback&, AddQueryHolderCallback, (SQLQueryHolderCallback&& callback), (override));\n'),
    ):
        require(after.count(anchor) == 1, "WorldMock correction anchor is absent or ambiguous")
        after = after.replace(anchor, anchor + addition)
    corrected = after.encode("utf-8")
    require(digest(corrected) == fixture["corrected_sha256"], "WorldMock corrected bytes differ from authorized result")
    require(hashlib.sha1(b"blob " + str(len(corrected)).encode() + b"\0" + corrected).hexdigest() ==
            fixture["corrected_git_blob"], "WorldMock corrected Git blob differs from authorization")
    delta = "".join(difflib.unified_diff(before.splitlines(keepends=True), after.splitlines(keepends=True),
                    fromfile="a/" + fixture["path"], tofile="b/" + fixture["path"])).encode()
    require(delta == FIXTURE_PATCH_PATH.read_bytes(), "WorldMock delta differs from the exact approved patch")
    return corrected


def apply_test_fixture(ac, policy, evidence):
    require(os.environ.get("GITHUB_ACTIONS") == "true" and os.environ.get("RUNNER_OS") == "Linux",
            "Corrected WorldMock may exist only inside the disposable Linux CI job")
    fixture = fixture_policy()
    require(fixture["core_commit"] == policy["core_commit"], "WorldMock exception pin differs from target")
    target = ac / fixture["path"]
    require(target.resolve() == target and target.is_file() and not target.is_symlink(), "WorldMock fixture is aliased or missing")
    original = target.read_bytes()
    corrected = corrected_fixture_bytes(original, fixture)
    require(git(ac, "show", policy["core_commit"] + ":" + fixture["path"]) == original,
            "WorldMock original differs from exact pinned source")
    # Evidence contains the small approved delta and identities, never the full header.
    (evidence / "worldmock-fixture.patch").write_bytes(FIXTURE_PATCH_PATH.read_bytes())
    target.write_bytes(corrected)
    report = {**fixture, "applied": True, "applied_sha256": digest(target.read_bytes()),
              "compiled_fixture": "AUTHORIZED_CORRECTED_TEST_FIXTURE_NOT_UNCHANGED_UPSTREAM",
              "build_started": False, "restored_before_install": False}
    require(report["applied_sha256"] == fixture["corrected_sha256"], "WorldMock application failed")
    return original, report


def verify_and_restore_test_fixture(ac, policy, original, report):
    """Verify the compiled delta before restoration; restoration never erases its receipt."""
    target = ac / report["path"]
    require(target.resolve() == target and target.is_file() and not target.is_symlink(), "Compiled WorldMock is aliased or missing")
    require(digest(target.read_bytes()) == report["corrected_sha256"], "WorldMock changed during compilation")
    require(git(ac, "rev-parse", "HEAD").decode().strip() == policy["core_commit"], "Core pin changed during fixture build")
    git(ac, "diff", "--cached", "--exit-code", policy["core_commit"], "--", ".")
    git(ac, "diff", "--exit-code", policy["core_commit"], "--", ".", ":(exclude)" + report["path"])
    bots = ac / "modules/mod-playerbots"
    require(git(bots, "rev-parse", "HEAD").decode().strip() == policy["playerbots_commit"], "Playerbots pin changed during fixture build")
    git(bots, "diff", "--exit-code", policy["playerbots_commit"], "--", ".")
    require(not git(bots, "status", "--porcelain", "--untracked-files=no").strip(), "Playerbots index/tree changed during fixture build")
    require(git(ac, "diff", "--name-only", policy["core_commit"], "--", ".").decode().splitlines() == [report["path"]],
            "Compiled dependency delta is not exactly the authorized fixture")
    report.update({"post_compile_sha256": digest(target.read_bytes()), "all_other_tracked_files_unchanged": True,
                   "post_compile_exact_delta_verified": True})
    require(digest(original) == report["original_sha256"], "Original fixture restoration bytes changed")
    target.write_bytes(original)
    report.update({"restored_sha256": digest(target.read_bytes()), "restored_before_install": True})
    require(report["restored_sha256"] == report["original_sha256"], "WorldMock restoration failed")


def verify_fixture_receipt(receipt):
    report = receipt.get("test_fixture", {})
    expected = fixture_policy()
    require(all(report.get(key) == value for key, value in expected.items()), "WorldMock receipt policy/identity changed")
    require(report.get("applied") is True and report.get("build_started") is True and report.get("post_compile_exact_delta_verified") is True and
            report.get("all_other_tracked_files_unchanged") is True and report.get("restored_before_install") is True,
            "WorldMock application/verification/restoration evidence is incomplete")
    require(report.get("applied_sha256") == report.get("post_compile_sha256") == expected["corrected_sha256"] and
            report.get("restored_sha256") == expected["original_sha256"], "WorldMock before/after receipt is inconsistent")


def verify_identity(ac, policy):
    ac = Path(ac).resolve()
    bots = ac / "modules/mod-playerbots"
    inventory = {"core_commit": policy["core_commit"], "playerbots_commit": policy["playerbots_commit"], "files": {}}
    for repo, pin in ((ac, policy["core_commit"]), (bots, policy["playerbots_commit"])):
        require(git(repo, "rev-parse", "HEAD").decode().strip() == pin,
                f"Dependency commit changed: {repo.name}")
        git(repo, "diff", "--exit-code", pin, "--", ".")
        require(not git(repo, "status", "--porcelain", "--untracked-files=no").strip(),
                f"Dependency tracked tree/index is not clean: {repo.name}")
        for item in git(repo, "ls-tree", "-rz", pin).split(b"\0"):
            if not item:
                continue
            metadata, relative = item.split(b"\t", 1)
            mode, kind, blob = metadata.decode().split()
            relative = relative.decode("utf-8")
            if Path(relative).suffix.lower() not in SOURCE_SUFFIXES:
                continue
            path = repo / relative
            require(mode in ("100644", "100755") and kind == "blob", f"Unsupported upstream source mode: {relative}")
            require(path.is_file() and not path.is_symlink() and path.resolve() == path,
                    f"Upstream source is absent or aliased: {relative}")
            raw = path.read_bytes()
            actual_blob = hashlib.sha1(b"blob " + str(len(raw)).encode() + b"\0" + raw).hexdigest()
            require(actual_blob == blob, f"Upstream bytes differ from pinned Git blob: {relative}")
            inventory["files"][path.as_posix()] = {"repository": "playerbots" if repo == bots else "azerothcore",
                "commit": pin, "path": relative, "git_blob": blob, "sha256": digest(raw)}
    require(inventory["files"], "Verified upstream source inventory is empty")
    return inventory


def inventory_identity(inventory):
    return {"core_commit": inventory["core_commit"], "playerbots_commit": inventory["playerbots_commit"],
            "tracked_source_files": len(inventory["files"]),
            "inventory_sha256": digest(json.dumps(inventory, sort_keys=True).encode())}


def verified_file(path, inventory):
    path = Path(path)
    require(path.is_absolute() and path.as_posix() in inventory["files"], f"Unverified diagnostic/source ownership: {path}")
    require(path.resolve() == path and path.is_file() and not path.is_symlink(), f"Aliased/missing upstream file: {path}")
    entry = inventory["files"][path.as_posix()]
    require(digest(path.read_bytes()) == entry["sha256"], f"Upstream file changed: {path}")
    return entry


def check_project_directives(path):
    text = Path(path).read_text(encoding="utf-8", errors="replace")
    # Physical diagnostics defeat #line renaming, but a GNU system linemarker or
    # diagnostic pragma can suppress the diagnostic entirely. Do not permit those
    # in project-owned or generated compilation material.
    pattern = r"(?m)^\s*#\s*(?:pragma\s+(?:GCC|clang)\s+(?:diagnostic|system_header)|\d+\s+\")|\b(?:_Pragma|__pragma)\s*\("
    require(not re.search(pattern, text), f"Project/generated diagnostic suppression or system linemarker: {path}")


def check_project_includes(path, include_dirs, inventory, ac, visited=None):
    """Check reachable project/generated headers without classifying a build tree as vendor code."""
    visited = visited if visited is not None else set()
    path = Path(path)
    if path in visited or path.as_posix() in inventory["files"]:
        return
    require(path.resolve() == path and path.is_file(), f"Aliased/missing project include: {path}")
    visited.add(path)
    check_project_directives(path)
    source = path.read_text(encoding="utf-8", errors="replace")
    for line in source.splitlines():
        directive = re.match(r'^\s*#\s*include\s+(.+)', line)
        if not directive:
            continue
        literal = re.match(r'[<"]([^>"]+)[>"]', directive[1])
        require(literal is not None, f"Unproven computed project include: {path}")
        name = literal[1]
        roots = [path.parent] + include_dirs
        candidates = [Path(name)] if Path(name).is_absolute() else [root / name for root in roots]
        found = next((target for target in candidates if target.is_file()), None)
        if found is None:
            continue # Compiler will diagnose missing project files; standard includes are external.
        require(found.resolve() == found, f"Aliased project include: {found}")
        if found.is_relative_to(ac):
            check_project_includes(found, include_dirs, inventory, ac, visited)


def verify_commands(ac, policy, commands_path, project, inventory=None):
    ac = Path(ac).resolve()
    inventory = inventory or verify_identity(ac, policy)
    data = Path(commands_path).read_bytes()
    commands = json.loads(data)
    require(isinstance(commands, list) and commands, "Missing/empty compile command inventory")
    require(re.fullmatch(r"mod-[a-z0-9][a-z0-9-]*", project) and project != "mod-playerbots",
            "A distinct candidate module identity is required")
    demotions = candidate_sources = 0
    progress_objects = []
    pinned_deps = None
    for entry in commands:
        directory = Path(entry["directory"])
        require(directory.is_absolute() and directory.resolve() == directory, "Aliased compiler directory")
        path = Path(entry["file"])
        path = directory / path if not path.is_absolute() else path
        require(path.resolve() == path, f"Aliased compiler source input: {path}")
        args = entry.get("arguments") or shlex.split(entry["command"])
        require(path.is_relative_to(ac), f"Compilation outside disposable source/build tree: {path}")
        require(not any(arg.startswith("@") for arg in args), f"Opaque compiler response file: {path}")
        start = 1 if args and args[0] in ("ccache", "/usr/bin/ccache") else 0
        require(len(args) > start and args[start] in ("/usr/bin/clang-18", "/usr/bin/clang++-18"),
                f"Unexpected compiler/launcher: {path}")
        require(args.count("-c") == 1 and args.index("-c") + 1 < len(args),
                f"Missing/ambiguous compiler source input: {path}")
        actual_input = Path(args[args.index("-c") + 1])
        actual_input = directory / actual_input if not actual_input.is_absolute() else actual_input
        require(actual_input.resolve() == actual_input, f"Aliased actual compiler input: {actual_input}")
        require(actual_input == path, f"Compiler source input differs from inventory metadata: {path}")
        require(args.count("-o") == 1 and args.index("-o") + 1 < len(args),
                f"Missing/ambiguous compiler output: {path}")
        output = Path(args[args.index("-o") + 1])
        output = (directory / output).resolve() if not output.is_absolute() else output.resolve()
        require(output.is_relative_to(ac / "build"), f"Compiler output outside build tree: {path}")
        progress_objects.append(output.relative_to(ac / "build").as_posix())
        require("-Werror" in args, f"Global warnings-as-errors missing: {path}")
        require(all(args.count(flag) == 1 for flag in PHYSICAL_FLAGS), f"Physical diagnostic/macro flags missing or duplicated: {path}")
        require(args[args.index("-Xclang") + 1] == "-fno-diagnostics-use-presumed-location", f"Unexpected frontend option: {path}")
        forbidden = ("-fdiagnostics-use-presumed-location", "-ffile-prefix-map", "-fmacro-prefix-map", "-fdebug-prefix-map",
                     "-ivfsoverlay", "-vfsoverlay", "-remap-file", "-include", "-imacros", "-fmodule", "-fno-caret-diagnostics", "-fno-diagnostics-show")
        require(not any(arg.startswith(forbidden) for arg in args), f"Unproven diagnostic/input remapping: {path}")
        require(not any(arg.startswith(("-fmacro-backtrace-limit=", "-ftemplate-backtrace-limit=")) and arg not in PHYSICAL_FLAGS for arg in args),
                f"Truncated diagnostic provenance: {path}")
        native_system = {"/usr/include/mysql"} | {
            (ac / "build/googletest/googletest-src" / suffix).as_posix()
            for suffix in ("googlemock", "googlemock/include", "googletest", "googletest/include")}
        for index, arg in enumerate(args):
            if arg == "-isystem":
                require(index + 1 < len(args) and args[index + 1] in native_system,
                        f"Non-native system include could suppress project warnings: {path}")
            elif arg.startswith(("-isystem", "-idirafter", "-isysroot", "--sysroot")):
                raise GateFailure(f"Unsupported system-header classification: {path}")
        if "-w" in args:
            # The pinned acore-dependency-interface deliberately uses -w for deps.
            # Preserve only tracked upstream deps, never candidate/core/generated inputs.
            if pinned_deps is None:
                pinned_deps = set(git(ac, "ls-tree", "-r", "--name-only",
                                      policy["core_commit"], "--", "deps").decode().splitlines())
            require(path.is_relative_to(ac / "deps") and path.relative_to(ac).as_posix() in pinned_deps,
                    f"Compiler warnings disabled outside pinned third-party deps: {path}")
        require("-Wno-everything" not in args, f"All compiler warnings suppressed: {path}")
        require(not any(arg.startswith("-Wno-error=") for arg in args),
                f"Unauthorized warning demotion: {path}")
        count = args.count(DEMOTION)
        upstream = path.as_posix() in inventory["files"]
        require(count == (1 if upstream else 0), f"Misplaced/missing upstream demotion: {path}")
        if upstream:
            verified_file(path, inventory)
            require(args.index(DEMOTION) > args.index("-Werror"), f"Upstream demotion ordering changed: {path}")
        else:
            require(path.is_relative_to(ac / "build") or path.is_relative_to(ac / "modules" / project),
                    f"Untracked source added to a dependency tree: {path}")
            check_project_directives(path)
        if path.is_relative_to(ac / "modules" / project):
            include_dirs = []
            for index, arg in enumerate(args):
                if arg in ("-I", "-isystem", "-iquote"):
                    include_dirs.append(Path(args[index + 1]))
                elif arg.startswith("-I") and len(arg) > 2:
                    include_dirs.append(Path(arg[2:]))
            include_dirs = [item if item.is_absolute() else directory / item for item in include_dirs]
            check_project_includes(path, include_dirs, inventory, ac)
        require("-Wno-unused-parameter" not in args, f"Hidden unused-parameter warning: {path}")
        demotions += count
        candidate_sources += path.is_relative_to(ac / "modules" / project)
        if path.is_relative_to(ac / "modules") or path.is_relative_to(ac / "src"):
            if not path.is_relative_to(ac / "src/test"):
                require(all(flag in args for flag in ("-Wall", "-Wextra", "-Werror")),
                        f"Core/module warning policy changed: {path}")
            require("-w" not in args, f"Module warnings disabled: {path}")
            # Existing pinned Clang exclusions only; custom suppression fails.
            known = {"-Wno-narrowing", "-Wno-deprecated-register", "-Wno-mismatched-tags", DEMOTION}
            require(all(not arg.startswith("-Wno-") or arg in known for arg in args),
                    f"Unexpected module warning suppression: {path}")
        compiler_args = [arg for arg in args if Path(arg).name in ("clang-18", "clang++-18")]
        require(len(compiler_args) == 1, f"Unexpected compiler command: {path}")
    for path in (ac / "modules" / project).rglob("*"):
        if path.is_file() and path.suffix.lower() in SOURCE_SUFFIXES:
            check_project_directives(path)
    require(demotions > 0, "No verified upstream compilation was classified")
    require(candidate_sources > 0, "Candidate module has no actual compilation")
    require(len(set(progress_objects)) == len(progress_objects), "Duplicate compiler output provenance")
    return {"sha256": digest(data), "commands": len(commands), "file_scoped_demotions": demotions,
            "candidate": project, "candidate_sources": candidate_sources,
            "progress_objects": sorted(progress_objects)}


def recognized_progress(line, receipt):
    match = BUILD_PROGRESS.fullmatch(line)
    if match:
        known = receipt.get("compile_commands", {}).get("progress_objects", [])
        require(match[1] in known, f"Build progress references an unknown compiler output: {line}")
        return True
    return bool(PROGRESS.fullmatch(line) and not WARNING.search(line) and not ERROR.search(line))


def validate_capture(raw, receipt, policy, inventory):
    require(receipt.get("capture_complete") is True, "Build log capture is incomplete")
    require(type(receipt.get("returncode")) is int and receipt["returncode"] == 0,
            "Complete build did not succeed")
    require(receipt.get("log_sha256") == digest(raw), "Build log changed or was truncated")
    require(receipt.get("stream_sha256") == digest(raw), "Persisted log differs from captured process bytes")
    require(raw and raw.endswith(b"\n"), "Build log is absent, empty, or lacks completion newline")
    text = raw.decode("utf-8", errors="strict")
    require(not CONTROL.search(text), "Terminal/control bytes in build log")
    require("\r" not in text.replace("\r\n", ""), "Carriage-return overwrite in build log")
    lines = text.splitlines()
    # The source tree has been restored before install, but this header was corrected
    # during compilation. Its diagnostics must never inherit unchanged-upstream status.
    inventory = {**inventory, "files": {path: entry for path, entry in inventory["files"].items()
                 if not (entry.get("repository") == "azerothcore" and entry.get("path") == "src/test/mocks/WorldMock.h")}}
    header = re.compile(r"^(.*):(\d+):(\d+): (warning|note): (.+)$")
    allowed = []
    summaries = 0
    for index, line in enumerate(lines):
        if recognized_progress(line, receipt):
            continue
        # Source excerpts may contain the words warning/error as ordinary code.
        if re.match(r"^\s*(?:\d+\s*\||\|)", line):
            continue
        require(not ERROR.search(line), f"Build error remains: {line}")
        match = header.fullmatch(line)
        if match:
            path, row, column, severity, message = match.groups()
            # Notes retain physical macro spelling/expansion provenance. A project
            # or unknown note makes an otherwise upstream warning ambiguous/fatal.
            entry = verified_file(path, inventory)
            source_lines = Path(path).read_bytes().splitlines()
            require(1 <= int(row) <= len(source_lines) and 1 <= int(column) <= len(source_lines[int(row) - 1]) + 1,
                    f"Invalid physical diagnostic location: {line}")
            if severity == "warning":
                require(re.search(r"\[-W[^\]]+\]$", message), f"Warning category missing: {line}")
                allowed.append({"diagnostic": line, "source": entry, "line": int(row), "column": int(column),
                                "log_line": index + 1, "following_context": lines[index + 1:index + 3]})
            continue
        summary = re.fullmatch(r"(\d+) warnings? generated\.", line)
        if summary:
            summaries += int(summary[1])
        elif WARNING.search(line) or re.search(r"\bnote:.*(?:skipp|expansion|backtrace)", line, re.IGNORECASE):
            raise GateFailure(f"Unallowlisted warning or warning summary: {line}")
    require(summaries == len(allowed), f"Warning summaries ({summaries}) do not match observed diagnostics ({len(allowed)})")
    return {"allowed_upstream_warning_count": len(allowed), "upstream_warnings": allowed,
            "upstream_inventory": inventory_identity(inventory)}


def write_json(path, value):
    Path(path).parent.mkdir(parents=True, exist_ok=True)
    Path(path).write_text(json.dumps(value, indent=2) + "\n", encoding="utf-8")


def describe_failed_capture(log_path, receipt):
    """Reporting only: observations never determine source identity or acceptance."""
    report = {"capture_integrity": "UNVERIFIED", "acceptance_authority": False,
              "notice": "NON-AUTHORITATIVE observations: capture integrity is not verified",
              "issues": [], "diagnostics": []}
    try:
        raw = Path(log_path).read_bytes()
    except OSError as error:
        report["issues"].append(f"Build log unavailable: {error}")
        return report

    checks = (
        (receipt.get("capture_complete") is True, "Capture was not completed"),
        (type(receipt.get("returncode")) is int, "Process exit status is absent"),
        (bool(raw) and raw.endswith(b"\n"), "Log is empty or lacks its final newline"),
        (receipt.get("log_sha256") == digest(raw), "Persisted log hash does not match receipt"),
        (receipt.get("stream_sha256") == digest(raw), "Log does not match captured process bytes"),
    )
    report["issues"].extend(message for passed, message in checks if not passed)
    try:
        text = raw.decode("utf-8", errors="strict")
    except UnicodeError:
        report["issues"].append("Log is not valid UTF-8; observations use replacement characters")
        text = raw.decode("utf-8", errors="replace")
    if CONTROL.search(text):
        report["issues"].append("Terminal/control bytes are present")
    if "\r" in text.replace("\r\n", ""):
        report["issues"].append("Carriage-return overwrite is present")
    if not report["issues"]:
        report["capture_integrity"] = "VERIFIED_CAPTURE"
        report["notice"] = "Observed process output only; source identity and acceptance are not established by this report"

    lines = text.splitlines()
    for index, line in enumerate(lines):
        if re.search(r"\b(?:warning|(?:fatal\s+)?error)\s*:", line, re.IGNORECASE):
            report["diagnostics"].append({"log_line": index + 1, "header": line,
                                          "following_context": lines[index + 1:index + 3]})
    return report


def build(ac, evidence, policy, project):
    ac, evidence = Path(ac).resolve(), Path(evidence).resolve()
    evidence.mkdir(parents=True, exist_ok=True)
    receipt = {"capture_complete": False, "started_at_unix": time.time(), "project": project}
    verdict = {"status": "FAIL", "authorization": policy["authorization"]}
    process = None
    fixture_original = None
    try:
        inventory = verify_identity(ac, policy)
        receipt["identity_before"] = inventory_identity(inventory)
        require(json.loads((evidence / "upstream-source-inventory.json").read_text()) == inventory,
                "Configure-time upstream inventory changed")
        receipt["compile_commands"] = verify_commands(ac, policy, ac / "build/compile_commands.json", project, inventory)
        command = ["cmake", "--build", str(ac / "build"), "--config", "Release",
                   "-j", str((os.cpu_count() or 1) + 1)]
        receipt["command"] = command
        fixture_original, receipt["test_fixture"] = apply_test_fixture(ac, policy, evidence)
        log_path = evidence / "build.log"
        # One reader owns raw stdout+stderr capture; write failure is fatal.
        with log_path.open("xb") as log:
            stream_hash = hashlib.sha256()
            process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            receipt["test_fixture"]["build_started"] = True
            while chunk := process.stdout.read1(65536):
                stream_hash.update(chunk)
                log.write(chunk)
                log.flush()
                sys.stdout.buffer.write(chunk)
                sys.stdout.buffer.flush()
            receipt["returncode"] = process.wait()
        receipt["capture_complete"] = True
        receipt["stream_sha256"] = stream_hash.hexdigest()
        raw = log_path.read_bytes()
        receipt["log_sha256"] = digest(raw)
        verify_and_restore_test_fixture(ac, policy, fixture_original, receipt["test_fixture"])
        fixture_original = None
        verify_fixture_receipt(receipt)
        after = verify_identity(ac, policy)
        receipt["identity_after"] = inventory_identity(after)
        require(receipt["identity_before"] == receipt["identity_after"], "Source identity changed during build")
        require(receipt["compile_commands"] ==
                verify_commands(ac, policy, ac / "build/compile_commands.json", project, after),
                "Compile command inventory changed during build")
        verdict.update(validate_capture(raw, receipt, policy, after))
        verdict["status"] = "PASS"
    except (GateFailure, OSError, ValueError, KeyError, UnicodeError) as error:
        verdict["failure"] = str(error)
        if process is not None and process.poll() is None:
            process.terminate()
            process.wait()
    finally:
        if fixture_original is not None:
            try:
                verify_and_restore_test_fixture(ac, policy, fixture_original, receipt["test_fixture"])
            except (GateFailure, OSError, ValueError, KeyError) as error:
                receipt["test_fixture"]["cleanup_failure"] = str(error)
                verdict["status"] = "FAIL"
                verdict.setdefault("failure", str(error))
        if "test_fixture" in receipt:
            verdict["test_fixture"] = receipt["test_fixture"]
        receipt["finished_at_unix"] = time.time()
        if verdict["status"] == "FAIL":
            # Preserve observations in the existing JSON job summary, even when an
            # unsuccessful build correctly exits before acceptance-log validation.
            # Reporting must never replace the original failure or make a PASS.
            try:
                verdict["diagnostic_observations"] = describe_failed_capture(evidence / "build.log", receipt)
            except (OSError, ValueError, TypeError, KeyError) as error:
                verdict["diagnostic_observations"] = {
                    "capture_integrity": "UNVERIFIED", "acceptance_authority": False,
                    "notice": "NON-AUTHORITATIVE: diagnostic reporting failed", "failure": str(error)}
        write_json(evidence / "build-receipt.json", receipt)
        write_json(evidence / "upstream-warning-verdict.json", verdict)
    print(json.dumps(verdict, indent=2), flush=True)
    require(verdict["status"] == "PASS", verdict.get("failure", "Build verification failed"))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("action", choices=("identity", "commands", "build", "check-log"))
    parser.add_argument("--ac", required=True, type=Path)
    parser.add_argument("--evidence", required=True, type=Path)
    parser.add_argument("--project", required=True)
    args = parser.parse_args()
    policy = load_policy()
    if args.action == "identity":
        value = verify_identity(args.ac, policy)
        fixture = fixture_policy()
        require(fixture["core_commit"] == policy["core_commit"], "Fixture proposal pin differs from target")
        corrected_fixture_bytes((args.ac / fixture["path"]).read_bytes(), fixture)
        write_json(args.evidence / "upstream-source-inventory.json", value)
        write_json(args.evidence / "source-identity-before.json", inventory_identity(value))
        print(json.dumps(inventory_identity(value)))
    elif args.action == "commands":
        value = verify_commands(args.ac, policy, args.ac / "build/compile_commands.json", args.project)
        write_json(args.evidence / "compile-command-provenance.json", value)
        print(json.dumps({key: value[key] for key in value if key != "progress_objects"}))
    elif args.action == "build":
        build(args.ac, args.evidence, policy, args.project)
    else:
        current = verify_identity(args.ac, policy)
        receipt = json.loads((args.evidence / "build-receipt.json").read_text(encoding="utf-8"))
        verify_fixture_receipt(receipt)
        require(receipt.get("project") == args.project, "Candidate identity in build receipt changed")
        require(receipt.get("identity_before") == inventory_identity(current) == receipt.get("identity_after"),
                "Pre/post identity receipts do not match verified source")
        value = validate_capture((args.evidence / "build.log").read_bytes(), receipt,
                                 policy, current)
        print(json.dumps(value))


if __name__ == "__main__":
    try:
        main()
    except (GateFailure, OSError, ValueError, KeyError, UnicodeError) as error:
        print(f"Official build gate rejected: {error}", file=sys.stderr)
        sys.exit(1)
