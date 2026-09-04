#!/usr/bin/env python3
"""Protected provenance regressions and a real Ubuntu compiler scope probe."""
import copy
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

import verify_build as gate

INTEGRATION = "--integration" in sys.argv
if INTEGRATION:
    sys.argv.remove("--integration")
TEMP_ROOT = Path(os.environ.get("RUNNER_TEMP", ".forge-local/validation-tests")).resolve()
TEMP_ROOT.mkdir(parents=True, exist_ok=True)


def receipt(raw, commands=None, code=0):
    return {"capture_complete": True, "returncode": code, "log_sha256": gate.digest(raw),
            "stream_sha256": gate.digest(raw), "compile_commands": commands or {"progress_objects": []}}


class ProvenanceTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(dir=TEMP_ROOT)
        self.root = Path(self.temp.name)
        self.ac = self.root / "ac"
        self.bots = self.ac / "modules/mod-playerbots"
        self.project = self.ac / "modules/mod-candidate"
        self.source = self.bots / "src/Upstream.cpp"
        self.header = self.ac / "src/Upstream.h"
        self.candidate = self.project / "src/Candidate.cpp"
        self.project_header = self.project / "src/Project.h"
        self.policy = gate.load_policy()
        self.ac.mkdir()
        self.init(self.ac)
        (self.ac / ".gitignore").write_text("/modules/\n/build/\n")
        self.header.parent.mkdir()
        self.header.write_text("inline int upstream_header() { return 1; }\n")
        self.policy["core_commit"] = self.commit(self.ac)
        self.source.parent.mkdir(parents=True)
        self.init(self.bots)
        self.source.write_text("int upstream(int unused) { return 1; }\n")
        self.policy["playerbots_commit"] = self.commit(self.bots)
        self.candidate.parent.mkdir(parents=True)
        self.candidate.write_text("int candidate() { return 1; }\n")
        self.project_header.write_text("// ordinary project header\n")
        self.inventory = gate.verify_identity(self.ac, self.policy)

    def tearDown(self):
        self.temp.cleanup()

    @staticmethod
    def init(path):
        subprocess.run(["git", "init", "-q", str(path)], check=True)
        for key, value in (("core.autocrlf", "false"), ("user.name", "Forge fixture"),
                           ("user.email", "forge-fixture@example.invalid"), ("commit.gpgsign", "false")):
            gate.git(path, "config", key, value)

    @staticmethod
    def commit(path):
        gate.git(path, "add", ".")
        gate.git(path, "commit", "-qm", "disposable pinned fixture")
        return gate.git(path, "rev-parse", "HEAD").decode().strip()

    def warning(self, path=None):
        path = path or self.source
        return (f"{path.as_posix()}:1:18: warning: unused parameter 'unused' [-Wunused-parameter]\n"
                "    1 | int upstream(int unused) { return 1; }\n"
                "      |                  ^\n1 warning generated.\n").encode()

    def commands(self):
        base = ["/usr/bin/clang++-18", "-Werror", "-Wall", "-Wextra"] + gate.PHYSICAL_FLAGS
        return [{"directory": str(self.ac / "build"), "file": str(path),
                 "arguments": base + ([gate.DEMOTION] if path == self.source else []) +
                 ["-o", str(index) + ".cpp.o", "-c", str(path)]}
                for index, path in enumerate((self.source, self.candidate))]

    def check_commands(self, rows):
        target = self.root / "commands.json"
        target.write_text(json.dumps(rows))
        return gate.verify_commands(self.ac, self.policy, target, "mod-candidate", self.inventory)

    def test_exact_inventory_and_command_scope(self):
        self.assertEqual(len(self.inventory["files"]), 2)
        info = self.check_commands(self.commands())
        self.assertEqual(info["file_scoped_demotions"], 1)
        self.assertEqual(info["candidate_sources"], 1)

    def test_changed_pin_and_staged_or_unstaged_source(self):
        with self.assertRaises(gate.GateFailure):
            gate.verify_identity(self.ac, {**self.policy, "playerbots_commit": "0" * 40})
        self.source.write_text("changed\n")
        with self.assertRaises(gate.GateFailure):
            gate.verify_identity(self.ac, self.policy)
        gate.git(self.bots, "add", ".")
        with self.assertRaises(gate.GateFailure):
            gate.verify_identity(self.ac, self.policy)

    def test_multiple_and_zero_verified_warnings(self):
        for raw, count in ((self.warning(), 1), (self.warning() * 3, 3), (b"[100%] Built target modules\n", 0)):
            result = gate.validate_capture(raw, receipt(raw), self.policy, self.inventory)
            self.assertEqual(result["allowed_upstream_warning_count"], count)

    def test_project_unknown_copied_and_generated_warning_paths_fail(self):
        for path in (self.candidate, self.project_header, self.ac / "build/Generated.cpp",
                     self.bots / "src/Untracked.cpp", self.source.parent / "../src/Upstream.cpp"):
            raw = self.warning(path)
            with self.subTest(path=path), self.assertRaises(gate.GateFailure):
                gate.validate_capture(raw, receipt(raw), self.policy, self.inventory)
        self.candidate.write_bytes(self.source.read_bytes())
        with self.assertRaises(gate.GateFailure):
            gate.verified_file(self.candidate, self.inventory)

    def test_changed_warning_source_bytes_fail(self):
        raw = self.warning()
        self.source.write_text("changed after inventory\n")
        with self.assertRaises(gate.GateFailure):
            gate.validate_capture(raw, receipt(raw), self.policy, self.inventory)

    def test_project_macro_note_is_fatal(self):
        raw = self.warning() + f"{self.project_header.as_posix()}:1:1: note: expanded from macro 'PROJECT'\n".encode()
        with self.assertRaises(gate.GateFailure):
            gate.validate_capture(raw, receipt(raw), self.policy, self.inventory)

    def test_upstream_header_warning_can_be_classified_but_errors_never_waived(self):
        raw = self.warning(self.header)
        self.assertEqual(gate.validate_capture(raw, receipt(raw), self.policy, self.inventory)["allowed_upstream_warning_count"], 1)
        for raw in (raw.replace(b"warning:", b"fatal error:"), b"clang: error: actual compiler error\n"):
            with self.assertRaises(gate.GateFailure):
                gate.validate_capture(raw, receipt(raw), self.policy, self.inventory)

    def test_missing_truncated_corrupt_failed_capture(self):
        raw = self.warning()
        for data, capture in ((b"", receipt(b"")), (raw[:-1], receipt(raw)),
                              (raw, {**receipt(raw), "capture_complete": False}),
                              (raw, {**receipt(raw), "stream_sha256": "0" * 64}),
                              (raw, receipt(raw, code=2)), (raw, receipt(raw, code=False)),
                              (b"\x1b[31m" + raw, receipt(b"\x1b[31m" + raw)),
                              (b"\r" + raw, receipt(b"\r" + raw))):
            with self.subTest(capture=capture), self.assertRaises(gate.GateFailure):
                gate.validate_capture(data, capture, self.policy, self.inventory)

    def test_unknown_warnings_and_summary_mismatch_fail(self):
        for raw in (self.warning().replace(b"1 warning generated.", b"2 warnings generated."),
                    self.warning().replace(b"1 warning generated.\n", b""),
                    self.warning() + b"clang: warning: unknown driver warning\n",
                    self.warning() + b"CMake Warning at CMakeLists.txt:1\n"):
            with self.assertRaises(gate.GateFailure):
                gate.validate_capture(raw, receipt(raw), self.policy, self.inventory)

    def test_candidate_or_unknown_demotion_and_missing_candidate_fail(self):
        rows = self.commands()
        rows[1]["arguments"].insert(1, gate.DEMOTION)
        with self.assertRaises(gate.GateFailure):
            self.check_commands(rows)
        with self.assertRaises(gate.GateFailure):
            self.check_commands(self.commands()[:1])
        rows = self.commands()
        rows[0]["file"] = str(self.bots / "src/Unknown.cpp")
        rows[0]["arguments"][-1] = rows[0]["file"]
        with self.assertRaises(gate.GateFailure):
            self.check_commands(rows)

    def test_source_binding_suppression_and_remapping_fail(self):
        for extra in ("-w", "-Wno-everything", "-Wno-unused-parameter", "-Wno-error=unused-parameter",
                      "-fmacro-backtrace-limit=1", "-fdiagnostics-use-presumed-location", "-ffile-prefix-map=x=y",
                      "-ivfsoverlay=fake", "-include=fake", "-isystem/fake"):
            rows = self.commands()
            rows[1]["arguments"].append(extra)
            with self.subTest(extra=extra), self.assertRaises(gate.GateFailure):
                self.check_commands(rows)
        rows = self.commands()
        rows[0]["arguments"][-1] = str(self.candidate)
        with self.assertRaises(gate.GateFailure):
            self.check_commands(rows)

    def test_system_linemarker_and_warning_pragmas_fail(self):
        for text in ('# 1 "upstream.h" 3\n', '#pragma GCC system_header\n',
                     '#pragma clang diagnostic ignored "-Wunused"\n', '_Pragma("GCC system_header")\n'):
            self.project_header.write_text(text)
            with self.subTest(text=text), self.assertRaises(gate.GateFailure):
                self.check_commands(self.commands())

    def test_generated_project_header_is_checked(self):
        generated = self.ac / "build/Generated.hpp"
        generated.parent.mkdir()
        generated.write_text("#pragma GCC system_header\ninline int hidden(int unused) { return 1; }\n")
        self.candidate.write_text(f'#include "{generated.as_posix()}"\nint candidate() {{ return 1; }}\n', encoding="utf-8")
        with self.assertRaises(gate.GateFailure):
            self.check_commands(self.commands())

    def test_native_dependency_warning_convention(self):
        dep = self.ac / "deps/Native.c"
        dep.parent.mkdir()
        dep.write_text("int native(void) { return 1; }\n")
        self.policy["core_commit"] = self.commit(self.ac)
        self.inventory = gate.verify_identity(self.ac, self.policy)
        rows = self.commands()
        item = copy.deepcopy(rows[0])
        item["file"] = str(dep)
        item["arguments"][-1] = str(dep)
        item["arguments"][item["arguments"].index("-o") + 1] = "native.o"
        item["arguments"].append("-w")
        self.check_commands(rows + [item])

    def test_failed_report_keeps_observations_non_authoritative(self):
        raw = self.warning()
        path = self.root / "build.log"
        path.write_bytes(raw)
        report = gate.describe_failed_capture(path, receipt(raw, code=2))
        self.assertEqual(report["capture_integrity"], "VERIFIED_CAPTURE")
        self.assertFalse(report["acceptance_authority"])
        self.assertEqual(len(report["diagnostics"]), 1)
        for capture in ({}, {**receipt(raw), "stream_sha256": "bad"}):
            self.assertEqual(gate.describe_failed_capture(path, capture)["capture_integrity"], "UNVERIFIED")

    @unittest.skipUnless(INTEGRATION, "real Ubuntu compiler probe requires --integration")
    def test_real_cmake_scope_headers_macros_and_physical_locations(self):
        for tool in ("cmake", "clang-18", "clang++-18"):
            self.assertIsNotNone(shutil.which(tool))
        self.source.write_text('#include "../../mod-candidate/src/Project.h"\nint upstream(int unused) { return 1; }\n')
        self.policy["playerbots_commit"] = self.commit(self.bots)
        (self.ac / "CMakeLists.txt").write_text('cmake_minimum_required(VERSION 3.24)\nproject(AzerothCore LANGUAGES CXX C)\nadd_subdirectory(modules)\n')
        (self.ac / "modules/CMakeLists.txt").write_text('add_library(modules STATIC mod-playerbots/src/Upstream.cpp mod-candidate/src/Candidate.cpp)\n')
        self.policy["core_commit"] = self.commit(self.ac)
        self.inventory = gate.verify_identity(self.ac, self.policy)
        inventory_path = self.root / "inventory.json"
        gate.write_json(inventory_path, self.inventory)
        configure = ["cmake", "-S", str(self.ac), "-B", str(self.ac / "build"),
                     "-DCMAKE_C_COMPILER=clang-18", "-DCMAKE_CXX_COMPILER=clang++-18",
                     "-DCMAKE_CXX_FLAGS=-Werror -Wall -Wextra -fno-color-diagnostics",
                     "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON", "-DCMAKE_COLOR_MAKEFILE=OFF",
                     f"-DCMAKE_PROJECT_AzerothCore_INCLUDE={Path(__file__).with_name('upstream-warning-hook.cmake').resolve()}",
                     f"-DFORGE_UPSTREAM_INVENTORY={inventory_path}"]
        result = subprocess.run(configure, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        self.assertEqual(result.returncode, 0, result.stdout.decode())
        commands = gate.verify_commands(self.ac, self.policy, self.ac / "build/compile_commands.json", "mod-candidate", self.inventory)

        def compile_now():
            return subprocess.run(["cmake", "--build", str(self.ac / "build"), "--clean-first", "-j", "2"],
                                  stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

        result = compile_now()
        self.assertEqual(result.returncode, 0, result.stdout.decode())
        gate.validate_capture(result.stdout, receipt(result.stdout, commands), self.policy, self.inventory)
        self.candidate.write_text("int candidate(int unused_project) { return 1; }\n")
        result = compile_now()
        self.assertNotEqual(result.returncode, 0)
        self.assertIn(b"unused_project", result.stdout)
        self.candidate.write_text("int candidate() { return 1; }\n")
        for text in ('inline int bad_header(int unused_project) { return 1; }\n',
                     f'#line 1 "{self.source.as_posix()}"\ninline int bad_header(int unused_project) {{ return 1; }}\n'):
            self.project_header.write_text(text)
            result = compile_now()
            self.assertEqual(result.returncode, 0, result.stdout.decode())
            self.assertIn(self.project_header.as_posix().encode(), result.stdout)
            with self.assertRaises(gate.GateFailure):
                gate.validate_capture(result.stdout, receipt(result.stdout, commands), self.policy, self.inventory)
        self.project_header.write_text('#define PROJECT_DIVIDE (1 / 0)\n')
        self.source.write_text('#include "../../mod-candidate/src/Project.h"\nint upstream(int unused) { return PROJECT_DIVIDE; }\n')
        self.policy["playerbots_commit"] = self.commit(self.bots)
        self.inventory = gate.verify_identity(self.ac, self.policy)
        result = compile_now()
        self.assertEqual(result.returncode, 0, result.stdout.decode())
        self.assertIn(b"expanded from macro", result.stdout)
        with self.assertRaises(gate.GateFailure):
            gate.validate_capture(result.stdout, receipt(result.stdout, commands), self.policy, self.inventory)
        self.project_header.write_text("// clear\n")
        self.header.write_text("inline int upstream_header(int unused_upstream) { return 1; }\n")
        self.policy["core_commit"] = self.commit(self.ac)
        self.candidate.write_text(f'#include "{self.header.as_posix()}"\nint candidate() {{ return 1; }}\n', encoding="utf-8")
        result = compile_now()
        self.assertNotEqual(result.returncode, 0, "Project TU must not silently demote header diagnostics")
        self.assertIn(b"unused_upstream", result.stdout)
        print("REAL_CMAKE_PROVENANCE_PROBE=PASS; upstream warnings visible, project/header/macro/spoof warnings rejected")


if __name__ == "__main__":
    unittest.main(verbosity=2)
