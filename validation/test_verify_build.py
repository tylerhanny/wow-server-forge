#!/usr/bin/env python3
"""Protected adversarial checks; --integration also requires real Ubuntu CMake/Clang."""

import copy
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

import verify_build as gate

INTEGRATION = "--integration" in sys.argv
if INTEGRATION:
    sys.argv.remove("--integration")
TEMP_ROOT = Path(os.environ.get("RUNNER_TEMP", ".forge-local/validation-tests")).resolve()
TEMP_ROOT.mkdir(parents=True, exist_ok=True)


def receipt(raw):
    return {"capture_complete": True, "returncode": 0, "log_sha256": gate.digest(raw),
            "stream_sha256": gate.digest(raw),
            "compile_commands": {"progress_objects": ["another.cpp.o", "src/Warning.cpp.o"]}}


def diagnostic(policy, source):
    return (
        f"{source.as_posix()}:107:60: warning: {policy['diagnostic']}\n"
        f"  107 | {policy['source_line']}\n"
        "      |                                                            ^\n"
        "1 warning generated.\n"
    ).encode()


class CaptureTests(unittest.TestCase):
    def setUp(self):
        self.policy = gate.load_policy()
        self.source = Path("/forge/ac/modules/mod-playerbots") / self.policy["path"]
        self.raw = diagnostic(self.policy, self.source) + b"[100%] Built target worldserver\n"

    def check(self, raw, capture=None):
        return gate.validate_capture(raw, capture or receipt(raw), self.policy, self.source)

    def test_exact_one_warning(self):
        self.assertEqual(self.check(self.raw)["allowed_warning_count"], 1)

    def test_interleaved_ordinary_progress(self):
        raw = self.raw.replace(b"\n  107", b"\n[ 84%] Building CXX object another.cpp.o\n  107", 1)
        self.assertEqual(self.check(raw)["allowed_warning_count"], 1)

    def test_inventory_backed_warning_filename_progress(self):
        self.assertEqual(self.check(self.raw + b"[99%] Building CXX object src/Warning.cpp.o\n")
                         ["allowed_warning_count"], 1)
        for progress in (b"[99%] Building CXX object forged.cpp.o 2 warnings generated.\n",
                         b"[99%] Building CXX object src/OtherWarning.cpp.o\n"):
            with self.subTest(progress=progress), self.assertRaises(gate.GateFailure):
                self.check(self.raw + progress)

    def test_changed_identity_or_diagnostic_is_rejected(self):
        cases = {
            "candidate spoof": self.raw.replace(b"mod-playerbots/", b"mod-candidate/"),
            "near path": self.raw.replace(b"BTHelpers.cpp", b"AlmostBTHelpers.cpp"),
            "relative path": self.raw.replace(b"/forge/ac/", b"ac/"),
            "path traversal": self.raw.replace(b"/src/", b"/src/../src/"),
            "wrong line": self.raw.replace(b":107:60:", b":108:60:"),
            "wrong column": self.raw.replace(b":107:60:", b":107:61:"),
            "wrong parameter": self.raw.replace(b"unused parameter 'botAI'", b"unused parameter 'bot'"),
            "wrong category": self.raw.replace(b"[-Wunused-parameter]", b"[-Wunused-variable]"),
            "wrong function": self.raw.replace(b"GetShahrazTankPositionState", b"OtherFunction"),
            "missing context": self.raw.replace(f"  107 | {self.policy['source_line']}\n".encode(), b""),
            "fake context separator": self.raw.replace(b"\n  107", b"\npretend context\n  107"),
        }
        for name, raw in cases.items():
            with self.subTest(name=name), self.assertRaises(gate.GateFailure):
                self.check(raw)

    def test_other_diagnostics_and_summaries_are_rejected(self):
        for extra in (
            b"/forge/ac/modules/mod-candidate/src/X.cpp:2:1: warning: unused parameter 'x' [-Wunused-parameter]\n",
            b"/forge/ac/src/Other.cpp:2:1: warning: something else [-Wother]\n",
            b"clang++-18: warning: driver diagnostic [-Wother]\n",
            b"CMake Warning at CMakeLists.txt:1 (message):\n",
            b"/forge/ac/modules/mod-candidate/src/X.cpp:2:1: error: bad source\n",
            b"unrecognized WARNING format\n",
            b"2 warnings generated.\n",
            b"1 warning generated.\n",
            diagnostic(self.policy, self.source),
        ):
            with self.subTest(extra=extra[:80]), self.assertRaises(gate.GateFailure):
                self.check(self.raw + extra)

    def test_incomplete_empty_cached_and_failed_capture(self):
        cases = [
            (b"", receipt(b"")),
            (b"[100%] Built target worldserver\n", receipt(b"[100%] Built target worldserver\n")),
            (self.raw.rstrip(b"\n"), receipt(self.raw.rstrip(b"\n"))),
            (self.raw.replace(b"1 warning generated.\n", b""), receipt(self.raw.replace(b"1 warning generated.\n", b""))),
            (self.raw, {**receipt(self.raw), "capture_complete": False}),
            (self.raw, {**receipt(self.raw), "returncode": 2}),
            (self.raw, {**receipt(self.raw), "returncode": False}),
            (self.raw[:-10], receipt(self.raw)),
            (self.raw, {"returncode": 0}),
            (self.raw, {**receipt(self.raw), "stream_sha256": "0" * 64}),
        ]
        for raw, capture in cases:
            with self.subTest(capture=capture), self.assertRaises(gate.GateFailure):
                self.check(raw, capture)

    def test_terminal_controls_rejected_and_crlf_supported(self):
        for control in (b"\x1b[31m", b"\r", b"\x00", b"\x08"):
            with self.subTest(control=control), self.assertRaises(gate.GateFailure):
                self.check(control + self.raw)
        crlf = self.raw.replace(b"\n", b"\r\n")
        self.assertEqual(self.check(crlf)["allowed_warning_count"], 1)


class FailureReportingTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=TEMP_ROOT)
        self.root = Path(self.temp.name)
        self.log = self.root / "build.log"
        self.policy = gate.load_policy()
        self.source = Path("/forge/ac/modules/mod-playerbots") / self.policy["path"]
        self.raw = diagnostic(self.policy, self.source) + (
            b"/forge/ac/modules/mod-playerbots/HyjalHelpers.cpp:168:61: fatal error: unused parameter 'botAI' [-Wunused-parameter]\n"
            b" 168 | TankPositionState GetKazrogalTankPositionState(PlayerbotAI* botAI, Player* bot)\n"
            b"     |                                                             ^\n"
            b"1 error generated.\n"
        )

    def tearDown(self):
        self.temp.cleanup()

    def test_failed_capture_exposes_warning_and_error_without_acceptance(self):
        self.log.write_bytes(self.raw)
        capture = {**receipt(self.raw), "returncode": 2}
        report = gate.describe_failed_capture(self.log, capture)
        self.assertEqual(report["capture_integrity"], "VERIFIED_CAPTURE")
        self.assertFalse(report["acceptance_authority"])
        self.assertEqual(len(report["diagnostics"]), 2)
        self.assertIn("BTHelpers.cpp:107:60: warning:", report["diagnostics"][0]["header"])
        self.assertIn("GetShahrazTankPositionState", report["diagnostics"][0]["following_context"][0])
        self.assertIn("fatal error:", report["diagnostics"][1]["header"])
        with self.assertRaisesRegex(gate.GateFailure, "Complete build did not succeed"):
            gate.validate_capture(self.raw, capture, self.policy, self.source)

    def test_partial_mismatched_and_stale_capture_is_non_authoritative(self):
        self.log.write_bytes(self.raw)
        cases = ({}, {**receipt(self.raw), "capture_complete": False},
                 {**receipt(self.raw), "log_sha256": "0" * 64},
                 {**receipt(self.raw), "stream_sha256": "0" * 64},
                 {**receipt(self.raw), "returncode": False})
        for capture in cases:
            with self.subTest(capture=capture):
                report = gate.describe_failed_capture(self.log, capture)
                self.assertEqual(report["capture_integrity"], "UNVERIFIED")
                self.assertIn("NON-AUTHORITATIVE", report["notice"])
                self.assertTrue(report["issues"])
                self.assertFalse(report["acceptance_authority"])

    def test_missing_empty_truncated_or_invalid_log_is_non_authoritative(self):
        report = gate.describe_failed_capture(self.log, {})
        self.assertEqual(report["diagnostics"], [])
        self.assertEqual(report["capture_integrity"], "UNVERIFIED")
        for raw in (b"", self.raw.rstrip(b"\n"), b"\x1b[31m" + self.raw,
                    b"\r" + self.raw, b"\xff" + self.raw):
            with self.subTest(raw=raw[:20]):
                self.log.write_bytes(raw)
                report = gate.describe_failed_capture(self.log, receipt(raw))
                self.assertEqual(report["capture_integrity"], "UNVERIFIED")
                self.assertIn("NON-AUTHORITATIVE", report["notice"])

    def test_early_failure_keeps_original_reason_and_labels_stale_log(self):
        self.log.write_bytes(self.raw)
        with mock.patch.object(gate, "verify_identity", side_effect=gate.GateFailure("original identity failure")), \
                mock.patch("sys.stdout", new=io.StringIO()), \
                self.assertRaisesRegex(gate.GateFailure, "original identity failure"):
            gate.build(self.root / "ac", self.root, self.policy, "mod-candidate")
        verdict = json.loads((self.root / "upstream-warning-verdict.json").read_text())
        self.assertEqual(verdict["status"], "FAIL")
        self.assertEqual(verdict["failure"], "original identity failure")
        self.assertEqual(verdict["diagnostic_observations"]["capture_integrity"], "UNVERIFIED")

    def test_failed_process_writes_observations_and_still_fails(self):
        process = mock.Mock(stdout=io.BytesIO(self.raw))
        process.wait.return_value = 2
        process.poll.return_value = 2
        output = mock.Mock(buffer=io.BytesIO())
        with mock.patch.object(gate, "verify_identity", return_value={}), \
                mock.patch.object(gate, "verify_commands", return_value={}), \
                mock.patch.object(gate.subprocess, "Popen", return_value=process), \
                mock.patch("sys.stdout", output), \
                self.assertRaisesRegex(gate.GateFailure, "Complete build did not succeed"):
            gate.build(self.root / "ac", self.root, self.policy, "mod-candidate")
        verdict = json.loads((self.root / "upstream-warning-verdict.json").read_text())
        self.assertEqual(verdict["status"], "FAIL")
        self.assertEqual(verdict["failure"], "Complete build did not succeed")
        self.assertEqual(verdict["diagnostic_observations"]["capture_integrity"], "VERIFIED_CAPTURE")
        self.assertEqual(len(verdict["diagnostic_observations"]["diagnostics"]), 2)


class GitFixture(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=TEMP_ROOT)
        self.ac = Path(self.temp.name) / "ac"
        self.bots = self.ac / "modules/mod-playerbots"
        self.policy = gate.load_policy()
        self.ac.mkdir()
        self.init_repo(self.ac)
        (self.ac / "core.txt").write_text("immutable core\n", encoding="utf-8")
        self.policy["core_commit"] = self.commit(self.ac)
        self.bots.mkdir(parents=True)
        self.init_repo(self.bots)
        self.source = gate.source_path(self.ac, self.policy)
        self.source.parent.mkdir(parents=True)
        self.source.write_bytes(b"\n" * 106 + self.policy["source_line"].encode() + b"\n{}\n")
        self.policy["playerbots_commit"] = self.commit(self.bots)
        self.policy["sha256"] = gate.digest(self.source.read_bytes())
        self.policy["git_blob"] = gate.git(self.bots, "rev-parse", f"HEAD:{self.policy['path']}").decode().strip()

    def tearDown(self):
        self.temp.cleanup()

    @staticmethod
    def init_repo(repo):
        subprocess.run(["git", "init", "-q", str(repo)], check=True)
        gate.git(repo, "config", "core.autocrlf", "false")
        gate.git(repo, "config", "user.name", "Forge fixture")
        gate.git(repo, "config", "user.email", "forge-fixture@example.invalid")
        gate.git(repo, "config", "commit.gpgsign", "false")

    @staticmethod
    def commit(repo):
        gate.git(repo, "add", ".")
        gate.git(repo, "commit", "-qm", "isolated fixture")
        return gate.git(repo, "rev-parse", "HEAD").decode().strip()

    def test_valid_source_identity(self):
        self.assertEqual(gate.verify_identity(self.ac, self.policy)["git_blob"], self.policy["git_blob"])

    def test_wrong_commit_blob_hash_and_line(self):
        for key, value in (
            ("core_commit", "0" * 40), ("playerbots_commit", "0" * 40),
            ("git_blob", "0" * 40), ("sha256", "0" * 64), ("source_line", "other function")):
            with self.subTest(key=key), self.assertRaises(gate.GateFailure):
                gate.verify_identity(self.ac, {**self.policy, key: value})

    def test_unstaged_and_staged_dependency_changes(self):
        self.source.write_bytes(self.source.read_bytes() + b"// mutated\n")
        with self.assertRaises(gate.GateFailure):
            gate.verify_identity(self.ac, self.policy)
        gate.git(self.bots, "add", self.policy["path"])
        with self.assertRaises(gate.GateFailure):
            gate.verify_identity(self.ac, self.policy)

    def test_core_mutation(self):
        (self.ac / "core.txt").write_text("changed\n", encoding="utf-8")
        with self.assertRaises(gate.GateFailure):
            gate.verify_identity(self.ac, self.policy)

    def commands(self):
        base = ["/usr/bin/clang++-18", "-Werror", "-Wall", "-Wextra"]
        return [
            {"directory": str(self.ac / "build"), "file": str(self.source),
             "arguments": base + [gate.DEMOTION, "-o", "modules/baseline.cpp.o", "-c", str(self.source)]},
            {"directory": str(self.ac / "build"), "file": str(self.ac / "modules/mod-candidate/src/X.cpp"),
             "arguments": base + ["-o", "modules/candidate.cpp.o", "-c", str(self.ac / "modules/mod-candidate/src/X.cpp")]},
        ]

    def check_commands(self, commands):
        path = Path(self.temp.name) / "compile_commands.json"
        path.write_text(json.dumps(commands), encoding="utf-8")
        return gate.verify_commands(self.ac, self.policy, path, "mod-candidate")

    def test_file_scoped_command_inventory(self):
        self.assertEqual(self.check_commands(self.commands())["file_scoped_demotions"], 1)

    def test_command_tampering(self):
        operations = [
            lambda c: c[1]["arguments"].append(gate.DEMOTION),
            lambda c: c[0]["arguments"].remove(gate.DEMOTION),
            lambda c: c[0]["arguments"].append(gate.DEMOTION),
            lambda c: c.append(copy.deepcopy(c[0])),
            lambda c: c[1]["arguments"].remove("-Werror"),
            lambda c: c[1]["arguments"].remove("-Wextra"),
            lambda c: c[1]["arguments"].append("-Wno-error"),
            lambda c: c[1]["arguments"].append("-Wno-unused-parameter"),
            lambda c: c[1]["arguments"].append("-Wno-shadow"),
            lambda c: c[1]["arguments"].append("-w"),
            lambda c: c[1]["arguments"].append("@hidden-flags"),
            lambda c: c[1]["arguments"].insert(0, "/usr/bin/echo"),
            lambda c: c[1]["arguments"].__setitem__(0, "/tmp/clang++-18"),
            lambda c: c[0]["arguments"].__setitem__(-1, c[1]["file"]),
        ]
        for index, operation in enumerate(operations):
            commands = self.commands()
            operation(commands)
            with self.subTest(operation=index), self.assertRaises(gate.GateFailure):
                self.check_commands(commands)

    def test_missing_candidate_and_core_suppression(self):
        for flag in ("-w", "-Wno-everything", "-Wno-shadow"):
            commands = self.commands()
            core = copy.deepcopy(commands[1])
            core["file"] = str(self.ac / "src/Other.cpp")
            core["arguments"][-1] = core["file"]
            core["arguments"][core["arguments"].index("-o") + 1] = "src/core.cpp.o"
            core["arguments"].append(flag)
            commands.append(core)
            with self.subTest(flag=flag), self.assertRaises(gate.GateFailure):
                self.check_commands(commands)
        commands = self.commands()
        commands[1]["file"] = str(self.bots / "src/Another.cpp")
        commands[1]["arguments"][-1] = commands[1]["file"]
        with self.assertRaises(gate.GateFailure):
            self.check_commands(commands)

    def test_only_pinned_dependency_sources_keep_native_w(self):
        dependency = self.ac / "deps/library/Dependency.cpp"
        dependency.parent.mkdir(parents=True)
        dependency.write_text("int dependency() { return 1; }\n", encoding="utf-8")
        gate.git(self.ac, "add", "deps/library/Dependency.cpp")
        gate.git(self.ac, "commit", "-qm", "pinned dependency fixture")
        self.policy["core_commit"] = gate.git(self.ac, "rev-parse", "HEAD").decode().strip()
        commands = self.commands()
        dep_command = copy.deepcopy(commands[1])
        dep_command["file"] = str(dependency)
        dep_command["arguments"][-1] = str(dependency)
        dep_command["arguments"][dep_command["arguments"].index("-o") + 1] = "deps/library.cpp.o"
        dep_command["arguments"].append("-w")
        commands.append(dep_command)
        self.check_commands(commands)
        dep_command["file"] = str(dependency.with_name("Untracked.cpp"))
        dep_command["arguments"][-1] = dep_command["file"]
        with self.assertRaises(gate.GateFailure):
            self.check_commands(commands)

    def test_pinned_test_sources_keep_existing_warning_configuration(self):
        commands = self.commands()
        core_test = copy.deepcopy(commands[1])
        core_test["file"] = str(self.ac / "src/test/ExistingTest.cpp")
        core_test["arguments"][-1] = core_test["file"]
        core_test["arguments"][core_test["arguments"].index("-o") + 1] = "src/test/existing.cpp.o"
        core_test["arguments"].remove("-Wall")
        core_test["arguments"].remove("-Wextra")
        commands.append(core_test)
        self.check_commands(commands)
        core_test["arguments"].append("-w")
        with self.assertRaises(gate.GateFailure):
            self.check_commands(commands)


class RealCMakeScopeTests(unittest.TestCase):
    @unittest.skipUnless(INTEGRATION, "real Ubuntu preflight requested with --integration")
    def test_real_cmake_file_scope_and_candidate_warning_failure(self):
        # This is a tiny actual configure/compile, not a claimed pinned-server build.
        for tool in ("cmake", "clang-18", "clang++-18"):
            self.assertIsNotNone(shutil.which(tool), f"Required real preflight tool missing: {tool}")
        with tempfile.TemporaryDirectory(dir=TEMP_ROOT) as temp:
            root = Path(temp)
            ac = root / "ac"
            source = ac / "modules/mod-playerbots/src/Ai/Raid/BT/BTHelpers.cpp"
            candidate = ac / "modules/mod-candidate/src/Probe.cpp"
            source.parent.mkdir(parents=True)
            candidate.parent.mkdir(parents=True)
            policy = gate.load_policy()
            prefix = "enum class TankPositionState { Unknown }; struct PlayerbotAI {}; struct Player {};\n"
            code = prefix + "\n" * 105 + policy["source_line"] + "\n{ (void)bot; return TankPositionState::Unknown; }\n"
            source.write_text(code, encoding="utf-8", newline="\n")
            self.assertEqual(source.read_text().splitlines()[106], policy["source_line"])
            candidate.write_text("int candidate_probe() { return 1; }\n", encoding="utf-8")
            hook_dir = root / "judge"
            hook_dir.mkdir()
            shutil.copyfile(Path(__file__).with_name("upstream-warning-hook.cmake"), hook_dir / "upstream-warning-hook.cmake")
            policy["sha256"] = gate.digest(source.read_bytes())
            (hook_dir / "upstream-warning-allowlist.json").write_text(json.dumps(policy), encoding="utf-8")
            (ac / "CMakeLists.txt").write_text(
                "cmake_minimum_required(VERSION 3.24)\nproject(AzerothCore LANGUAGES CXX C)\nadd_subdirectory(modules)\n",
                encoding="utf-8")
            (ac / "modules/CMakeLists.txt").write_text(
                "add_library(modules STATIC mod-playerbots/src/Ai/Raid/BT/BTHelpers.cpp mod-candidate/src/Probe.cpp)\n",
                encoding="utf-8")
            configure = [
                "cmake", "-S", str(ac), "-B", str(ac / "build"),
                "-DCMAKE_C_COMPILER=clang-18", "-DCMAKE_CXX_COMPILER=clang++-18",
                "-DCMAKE_C_FLAGS=-Werror -Wall -Wextra -fno-color-diagnostics",
                "-DCMAKE_CXX_FLAGS=-Werror -Wall -Wextra -fno-color-diagnostics",
                "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON", "-DCMAKE_COLOR_MAKEFILE=OFF",
                f"-DCMAKE_PROJECT_AzerothCore_INCLUDE={hook_dir / 'upstream-warning-hook.cmake'}",
            ]
            result = subprocess.run(configure, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            self.assertEqual(result.returncode, 0, result.stdout.decode())
            inventory = gate.verify_commands(ac, policy, ac / "build/compile_commands.json", "mod-candidate")
            result = subprocess.run(["cmake", "--build", str(ac / "build"), "-j", "2"],
                                    stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            self.assertEqual(result.returncode, 0, result.stdout.decode())
            gate.validate_capture(result.stdout, {**receipt(result.stdout), "compile_commands": inventory}, policy, source)
            candidate.write_text("int candidate_probe(int unused_candidate) { return 1; }\n", encoding="utf-8")
            result = subprocess.run(["cmake", "--build", str(ac / "build"), "--clean-first", "-j", "2"],
                                    stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
            self.assertNotEqual(result.returncode, 0, "Candidate warning was incorrectly demoted")
            self.assertIn(b"unused_candidate", result.stdout)
            self.assertIn(b"error:", result.stdout)
            with self.assertRaises(gate.GateFailure):
                gate.validate_capture(result.stdout, {**receipt(result.stdout), "returncode": result.returncode,
                                                       "compile_commands": inventory},
                                      policy, source)
            print("REAL_CMAKE_SCOPE_PROBE=PASS; exact source warned, candidate warning remained fatal")


if __name__ == "__main__":
    unittest.main(verbosity=2)
