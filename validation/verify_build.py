#!/usr/bin/env python3
"""Independent exact-warning gate; candidate-provided acceptance code is never used."""

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys
import time

POLICY_PATH = Path(__file__).with_name("upstream-warning-allowlist.json")
DEMOTION = "-Wno-error=unused-parameter"
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
    require(type(policy["expected_count"]) is int and policy["expected_count"] == 1,
            "Policy must require exactly one diagnostic")
    require(policy["path"] == "src/Ai/Raid/BT/BTHelpers.cpp", "Unexpected policy source path")
    require(policy["line"] == 107 and policy["column"] == 60, "Unexpected diagnostic location")
    require(policy["function"] == "GetShahrazTankPositionState", "Unexpected function")
    require(policy["diagnostic"] == "unused parameter 'botAI' [-Wunused-parameter]",
            "Unexpected diagnostic allowance")
    return policy


def git(repo, *args):
    result = subprocess.run(
        ["git", "--no-replace-objects", "-C", str(repo), *args],
        check=False, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        env={**os.environ, "GIT_NO_REPLACE_OBJECTS": "1"})
    require(result.returncode == 0, f"Git identity/integrity check failed: {' '.join(args)}")
    return result.stdout


def source_path(ac, policy):
    return Path(ac).resolve() / "modules" / "mod-playerbots" / policy["path"]


def verify_identity(ac, policy):
    ac = Path(ac).resolve()
    bots = ac / "modules/mod-playerbots"
    for repo, pin in ((ac, policy["core_commit"]), (bots, policy["playerbots_commit"])):
        require(git(repo, "rev-parse", "HEAD").decode().strip() == pin,
                f"Dependency commit changed: {repo.name}")
        git(repo, "diff", "--exit-code", pin, "--", ".")
        require(not git(repo, "status", "--porcelain", "--untracked-files=no").strip(),
                f"Dependency tracked tree/index is not clean: {repo.name}")
    source = source_path(ac, policy)
    require(source.is_file() and not source.is_symlink(), "Allowed source is absent or symlinked")
    require(source.resolve() == source, "Allowed source traverses a symlink")
    blob = git(bots, "rev-parse", f"{policy['playerbots_commit']}:{policy['path']}").decode().strip()
    require(blob == policy["git_blob"], "Pinned source Git blob mismatch")
    data = source.read_bytes()
    require(digest(data) == policy["sha256"], "Allowed source bytes changed")
    require(git(bots, "show", f"{policy['playerbots_commit']}:{policy['path']}") == data,
            "Working source differs from pinned blob")
    lines = data.decode("utf-8").splitlines()
    require(len(lines) >= policy["line"] and lines[policy["line"] - 1] == policy["source_line"],
            "Allowed function/source line mismatch")
    require(policy["function"] in policy["source_line"], "Function identity mismatch")
    return {key: policy[key] for key in
            ("core_commit", "playerbots_commit", "path", "git_blob", "sha256", "line", "function")}


def verify_commands(ac, policy, commands_path, project):
    ac = Path(ac).resolve()
    allowed = source_path(ac, policy)
    data = Path(commands_path).read_bytes()
    commands = json.loads(data)
    require(isinstance(commands, list) and commands, "Missing/empty compile command inventory")
    require(re.fullmatch(r"mod-[a-z0-9][a-z0-9-]*", project) and project != "mod-playerbots",
            "A distinct candidate module identity is required")
    demotions = source_occurrences = candidate_sources = 0
    progress_objects = []
    pinned_deps = None
    for entry in commands:
        directory = Path(entry["directory"]).resolve()
        path = Path(entry["file"])
        path = (directory / path).resolve() if not path.is_absolute() else path.resolve()
        args = entry.get("arguments") or shlex.split(entry["command"])
        require(path.is_relative_to(ac), f"Compilation outside disposable source/build tree: {path}")
        require(not any(arg.startswith("@") for arg in args), f"Opaque compiler response file: {path}")
        start = 1 if args and args[0] in ("ccache", "/usr/bin/ccache") else 0
        require(len(args) > start and args[start] in ("/usr/bin/clang-18", "/usr/bin/clang++-18"),
                f"Unexpected compiler/launcher: {path}")
        require(args.count("-c") == 1 and args.index("-c") + 1 < len(args),
                f"Missing/ambiguous compiler source input: {path}")
        actual_input = Path(args[args.index("-c") + 1])
        actual_input = (directory / actual_input).resolve() if not actual_input.is_absolute() else actual_input.resolve()
        require(actual_input == path, f"Compiler source input differs from inventory metadata: {path}")
        require(args.count("-o") == 1 and args.index("-o") + 1 < len(args),
                f"Missing/ambiguous compiler output: {path}")
        output = Path(args[args.index("-o") + 1])
        output = (directory / output).resolve() if not output.is_absolute() else output.resolve()
        require(output.is_relative_to(ac / "build"), f"Compiler output outside build tree: {path}")
        progress_objects.append(output.relative_to(ac / "build").as_posix())
        require("-Werror" in args, f"Global warnings-as-errors missing: {path}")
        if "-w" in args:
            # The pinned acore-dependency-interface deliberately uses -w for deps.
            # Preserve only tracked upstream deps, never candidate/core/generated inputs.
            if pinned_deps is None:
                pinned_deps = set(git(ac, "ls-tree", "-r", "--name-only",
                                      policy["core_commit"], "--", "deps").decode().splitlines())
            require(path.is_relative_to(ac / "deps") and path.relative_to(ac).as_posix() in pinned_deps,
                    f"Compiler warnings disabled outside pinned third-party deps: {path}")
        require("-Wno-everything" not in args, f"All compiler warnings suppressed: {path}")
        require(not any(arg == "-Wno-error" or
                        (arg.startswith("-Wno-error=") and arg != DEMOTION) for arg in args),
                f"Unauthorized warning demotion: {path}")
        count = args.count(DEMOTION)
        require(count == (1 if path == allowed else 0), f"Misplaced/missing baseline demotion: {path}")
        require("-Wno-unused-parameter" not in args, f"Hidden unused-parameter warning: {path}")
        demotions += count
        source_occurrences += path == allowed
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
    require(demotions == 1 and source_occurrences == 1, "Allowance must affect exactly one compilation")
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


def validate_capture(raw, receipt, policy, source):
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
    diagnostic = f"{Path(source).as_posix()}:{policy['line']}:{policy['column']}: warning: {policy['diagnostic']}"
    source_line = re.compile(rf"^\s*{policy['line']}\s*\|\s*{re.escape(policy['source_line'])}$")
    allowed = summaries = 0
    for index, line in enumerate(lines):
        require(not ERROR.search(line), f"Build error remains: {line}")
        if recognized_progress(line, receipt):
            continue
        if not WARNING.search(line):
            continue
        if line == diagnostic:
            context = index + 1
            while context < len(lines) and recognized_progress(lines[context], receipt):
                context += 1
            require(context < len(lines) and source_line.fullmatch(lines[context]),
                    "Allowed diagnostic lacks its exact function/source excerpt")
            allowed += 1
        elif line == "1 warning generated.":
            summaries += 1
        else:
            raise GateFailure(f"Unallowlisted warning or warning summary: {line}")
    require(allowed == policy["expected_count"], f"Expected one exact warning, found {allowed}")
    require(summaries == 1, f"Expected one complete single-warning summary, found {summaries}")
    return {"allowed_warning_count": allowed, "diagnostic": diagnostic,
            "function": policy["function"], "source_sha256": policy["sha256"]}


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
    try:
        receipt["identity_before"] = verify_identity(ac, policy)
        receipt["compile_commands"] = verify_commands(ac, policy, ac / "build/compile_commands.json", project)
        command = ["cmake", "--build", str(ac / "build"), "--config", "Release",
                   "-j", str((os.cpu_count() or 1) + 1)]
        receipt["command"] = command
        log_path = evidence / "build.log"
        # One reader owns raw stdout+stderr capture; write failure is fatal.
        with log_path.open("xb") as log:
            stream_hash = hashlib.sha256()
            process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
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
        receipt["identity_after"] = verify_identity(ac, policy)
        require(receipt["identity_before"] == receipt["identity_after"], "Source identity changed during build")
        require(receipt["compile_commands"] ==
                verify_commands(ac, policy, ac / "build/compile_commands.json", project),
                "Compile command inventory changed during build")
        verdict.update(validate_capture(raw, receipt, policy, source_path(ac, policy)))
        verdict["status"] = "PASS"
    except (GateFailure, OSError, ValueError, KeyError, UnicodeError) as error:
        verdict["failure"] = str(error)
        if process is not None and process.poll() is None:
            process.terminate()
            process.wait()
    finally:
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
        write_json(args.evidence / "source-identity-before.json", value)
        print(json.dumps(value))
    elif args.action == "commands":
        value = verify_commands(args.ac, policy, args.ac / "build/compile_commands.json", args.project)
        write_json(args.evidence / "compile-command-provenance.json", value)
        print(json.dumps({key: value[key] for key in value if key != "progress_objects"}))
    elif args.action == "build":
        build(args.ac, args.evidence, policy, args.project)
    else:
        current = verify_identity(args.ac, policy)
        receipt = json.loads((args.evidence / "build-receipt.json").read_text(encoding="utf-8"))
        require(receipt.get("project") == args.project, "Candidate identity in build receipt changed")
        require(receipt.get("identity_before") == current == receipt.get("identity_after"),
                "Pre/post identity receipts do not match verified source")
        value = validate_capture((args.evidence / "build.log").read_bytes(), receipt,
                                 policy, source_path(args.ac, policy))
        print(json.dumps(value))


if __name__ == "__main__":
    try:
        main()
    except (GateFailure, OSError, ValueError, KeyError, UnicodeError) as error:
        print(f"Official build gate rejected: {error}", file=sys.stderr)
        sys.exit(1)
