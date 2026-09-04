import copy
import hashlib
import importlib.util
import inspect
import json
import subprocess
import sys
from pathlib import Path

snapshot = Path(sys.argv[1]).resolve()
spec = importlib.util.spec_from_file_location('audited_verifier', snapshot / 'verify_build.py')
gate = importlib.util.module_from_spec(spec)
spec.loader.exec_module(gate)
policy = gate.load_policy(snapshot / 'upstream-warning-allowlist.json')
ac = snapshot / 'fixture-ac'
source = ac / 'modules/mod-playerbots' / policy['path']
candidate = ac / 'modules/mod-audit/src/Audit.cpp'
core = ac / 'src/server/game/World/World.cpp'
ac.mkdir(exist_ok=True)
baseline_object = 'modules/CMakeFiles/modules.dir/mod-playerbots/src/Ai/Raid/BT/BTHelpers.cpp.o'
benign_warning_object = 'modules/CMakeFiles/modules.dir/mod-audit/src/Warning.cpp.o'
diag = f"{source.as_posix()}:107:60: warning: unused parameter 'botAI' [-Wunused-parameter]"
excerpt = '  107 | ' + policy['source_line']
baseline = '\n'.join([
    '[  1%] Building CXX object modules/CMakeFiles/modules.dir/mod-playerbots/src/Ai/Raid/BT/BTHelpers.cpp.o',
    diag, excerpt, '      |                                                            ^',
    '1 warning generated.', '[100%] Built target worldserver', ''])
results = []

def run(name, expected, action):
    try:
        action()
        actual, detail = 'PASS', ''
    except Exception as exc:
        actual, detail = 'REJECT', f'{type(exc).__name__}: {exc}'
    results.append(dict(case=name, expected=expected, actual=actual,
                        matches=actual == expected, detail=detail))

def logcase(name, expected='REJECT', text=None, raw=None, receipt_changes=None):
    if raw is None:
        raw = (baseline if text is None else text).encode()
    receipt = dict(capture_complete=True, returncode=0, log_sha256=hashlib.sha256(raw).hexdigest(),
                   stream_sha256=hashlib.sha256(raw).hexdigest(),
                   compile_commands={'progress_objects': [baseline_object, benign_warning_object]})
    receipt.update(receipt_changes or {})
    run(name, expected, lambda: gate.validate_capture(raw, receipt, policy, source))

logcase('canonical_complete_log', 'PASS')
logcase('legitimate_parallel_progress', 'PASS', text=baseline.replace(excerpt, '[ 50%] Built target game\n' + excerpt))
logcase('crlf_without_overwrite', 'PASS', text=baseline.replace('\n', '\r\n'))
logcase('zero_allowed_warning', text='[100%] Built target worldserver\n')
logcase('two_allowed_warnings', text=baseline + diag + '\n' + excerpt + '\n1 warning generated.\n')
logcase('wrong_parameter', text=baseline.replace("parameter 'botAI'", "parameter 'bot'"))
logcase('wrong_function_excerpt', text=baseline.replace('GetShahrazTankPositionState', 'GetOtherTankPositionState'))
logcase('wrong_line', text=baseline.replace(':107:60:', ':108:60:'))
logcase('wrong_column', text=baseline.replace(':107:60:', ':107:59:'))
logcase('wrong_category', text=baseline.replace('[-Wunused-parameter]', '[-Wunused-variable]'))
logcase('same_basename_other_directory', text=baseline.replace(source.as_posix(), (ac / 'modules/mod-audit/src/BTHelpers.cpp').as_posix()))
logcase('candidate_lookalike_path_suffix', text=baseline.replace(source.as_posix(), (ac / 'modules/mod-audit/ac/modules/mod-playerbots' / policy['path']).as_posix()))
logcase('relative_allowed_path', text=baseline.replace(source.as_posix(), 'ac/modules/mod-playerbots/' + policy['path']))
logcase('path_traversal_alias', text=baseline.replace('/BT/BTHelpers.cpp:107', '/BT/../BT/BTHelpers.cpp:107'))
logcase('candidate_unused_parameter', text=baseline + f"{candidate.as_posix()}:9:1: warning: unused parameter 'botAI' [-Wunused-parameter]\n")
logcase('other_upstream_warning', text=baseline + f"{source.as_posix()}:11:1: warning: unused variable 'x' [-Wunused-variable]\n")
logcase('driver_warning', text=baseline + 'clang++-18: warning: argument unused during compilation [-Wunused-command-line-argument]\n')
logcase('linker_warning', text=baseline + '/usr/bin/ld: warning: missing .note.GNU-stack section implies executable stack\n')
logcase('no_path_warning', text=baseline + 'warning: generic unexpected warning\n')
logcase('unrelated_compile_error', text=baseline + f'{candidate.as_posix()}:9:1: error: no matching function\n')
logcase('fatal_error', text=baseline + 'fatal error: invalid source\n')
logcase('ansi_diagnostic', text=baseline.replace('warning:', '\x1b[33mwarning:\x1b[0m'))
logcase('ansi_hidden_extra_warning', text=baseline + '\x1b[2K\rwarning: concealed\n')
logcase('backspace', text=baseline + 'warr\bning: hidden\n')
logcase('null_byte', raw=baseline.encode() + b'\x00\n')
logcase('bare_carriage_return', text=baseline + '\roverwrite\n')
logcase('empty_log', raw=b'')
logcase('non_utf8', raw=baseline.encode() + b'\xff\n')
logcase('missing_final_newline', raw=baseline.encode().rstrip(b'\n'))
logcase('stale_log_hash', receipt_changes={'log_sha256': '0' * 64})
logcase('stream_hash_mismatch', receipt_changes={'stream_sha256': '0' * 64})
logcase('incomplete_capture_receipt', receipt_changes={'capture_complete': False})
logcase('missing_capture_receipt', receipt_changes={'capture_complete': None})
logcase('nonzero_build_status', receipt_changes={'returncode': 2})
logcase('missing_build_status', receipt_changes={'returncode': None})
logcase('boolean_build_status', receipt_changes={'returncode': False})
logcase('missing_summary', text=baseline.replace('1 warning generated.\n', ''))
logcase('extra_summary', text=baseline + '1 warning generated.\n')
logcase('mismatched_summary_count', text=baseline.replace('1 warning generated.', '2 warnings generated.'))
logcase('missing_source_excerpt', text=baseline.replace(excerpt + '\n', ''))
logcase('misleading_warning_source_filename', 'PASS', text=baseline + '[ 99%] Building CXX object modules/CMakeFiles/modules.dir/mod-audit/src/Warning.cpp.o\n')
logcase('forged_progress_hides_warning', text=baseline + '[ 99%] Building CXX object forged.cpp.o warning: unexpected diagnostic\n')
logcase('forged_progress_hides_warning_summary', text=baseline + '[ 99%] Building CXX object forged.cpp.o 2 warnings generated.\n')
logcase('unlisted_build_object', text=baseline + '[ 99%] Building CXX object modules/CMakeFiles/modules.dir/mod-audit/src/Unlisted.cpp.o\n')

def command(path, demote=False):
    args = ['/usr/bin/clang++-18', '-Wall', '-Wextra', '-Werror']
    if demote:
        args.append(gate.DEMOTION)
    output = ac / 'build' / (path.relative_to(ac).as_posix() + '.o')
    args += ['-c', path.as_posix(), '-o', output.as_posix()]
    return dict(directory=(ac / 'build').as_posix(), file=path.as_posix(), arguments=args)

inventory = [command(source, True), command(candidate), command(core)]
commands_path = snapshot / 'audit-compile-commands.json'

def commandcase(name, entries, expected='REJECT', command_policy=None):
    def action():
        commands_path.write_text(json.dumps(entries))
        if 'project' in inspect.signature(gate.verify_commands).parameters:
            gate.verify_commands(ac, command_policy or policy, commands_path, 'mod-audit')
        else:
            gate.verify_commands(ac, policy, commands_path)
    run(name, expected, action)

commandcase('canonical_scoped_demotion', inventory, 'PASS')
bad = copy.deepcopy(inventory); bad[1]['arguments'].insert(1, gate.DEMOTION)
commandcase('candidate_demotion', bad)
bad = copy.deepcopy(inventory); bad[0]['arguments'].remove(gate.DEMOTION)
commandcase('missing_baseline_demotion', bad)
bad = copy.deepcopy(inventory); bad[0]['arguments'].insert(1, gate.DEMOTION)
commandcase('duplicate_baseline_demotion', bad)
bad = copy.deepcopy(inventory); bad[1]['arguments'].insert(1, '-w')
commandcase('candidate_warnings_disabled', bad)
bad = copy.deepcopy(inventory); bad[1]['arguments'].insert(1, '-Wno-error')
commandcase('candidate_global_demotion', bad)
bad = copy.deepcopy(inventory); bad[1]['arguments'].insert(1, '-Wno-unused-variable')
commandcase('candidate_warning_suppression', bad)
bad = copy.deepcopy(inventory); bad[1]['arguments'].insert(1, '@hidden-flags.rsp')
commandcase('candidate_response_file', bad)
bad = copy.deepcopy(inventory); bad[1]['arguments'].remove('-Werror')
commandcase('candidate_werror_absent', bad)
bad = copy.deepcopy(inventory); bad[0]['arguments'][bad[0]['arguments'].index('-c') + 1] = candidate.as_posix()
commandcase('allowed_manifest_but_compiles_candidate', bad)
bad = copy.deepcopy(inventory); bad[2]['arguments'].insert(1, '-w')
commandcase('core_warnings_disabled', bad)
bad = copy.deepcopy(inventory); bad[2]['arguments'].insert(1, '-Wno-everything')
commandcase('core_all_warnings_suppressed', bad)
bad = copy.deepcopy(inventory); bad[2]['arguments'].insert(1, '-Wno-unused-variable')
commandcase('core_warning_suppression', bad)
bad = copy.deepcopy(inventory); bad[2]['arguments'].insert(1, '-Wno-unused-parameter')
commandcase('core_unused_parameter_hidden', bad)
other_bots = ac / 'modules/mod-playerbots/src/Other.cpp'
commandcase('no_candidate_compilation_in_inventory', [command(source, True), command(other_bots)])
commandcase('empty_command_inventory', [])
commandcase('duplicate_allowed_compilation', [*inventory, command(source, True)])
bad = copy.deepcopy(inventory); bad[1]['arguments'][bad[1]['arguments'].index('-o') + 1] = bad[0]['arguments'][bad[0]['arguments'].index('-o') + 1]
commandcase('duplicate_output_object', bad)
bad = copy.deepcopy(inventory); bad[1]['arguments'][bad[1]['arguments'].index('-o') + 1] = (ac / 'outside-build.o').as_posix()
commandcase('object_output_outside_build', bad)

# Native source policy has a different warning interface for third-party deps
# and unit_tests. Exercise that boundary with a real disposable Git inventory;
# this fixture commit is not represented as the actual AzerothCore pin.
tracked_dep = ac / 'deps/fmt/fmt/format.cc'
untracked_dep = ac / 'deps/fmt/fmt/Injected.cc'
test_source = ac / 'src/test/audit_test.cpp'
tracked_dep.parent.mkdir(parents=True, exist_ok=True)
tracked_dep.write_text('// disposable inventory fixture\n')
subprocess.run(['git', 'init', '-q', str(ac)], check=True)
subprocess.run(['git', '-C', str(ac), 'add', 'deps/fmt/fmt/format.cc'], check=True)
subprocess.run(['git', '-C', str(ac), '-c', 'user.name=Forge Fixture', '-c',
                'user.email=fixture@example.invalid', 'commit', '-q', '--allow-empty',
                '-m', 'Disposable tracked dependency fixture'], check=True)
fixture_pin = subprocess.check_output(['git', '-C', str(ac), 'rev-parse', 'HEAD'], text=True).strip()
fixture_policy = dict(policy, core_commit=fixture_pin)
dep_command = command(tracked_dep)
dep_command['arguments'] = [a for a in dep_command['arguments'] if a not in ('-Wall', '-Wextra')]
dep_command['arguments'].insert(1, '-w')
commandcase('pinned_tracked_dependency_native_w', [*inventory, dep_command], 'PASS', fixture_policy)
bad_dep = copy.deepcopy(dep_command)
bad_dep['file'] = untracked_dep.as_posix()
bad_dep['arguments'][bad_dep['arguments'].index('-c') + 1] = untracked_dep.as_posix()
commandcase('untracked_dependency_w', [*inventory, bad_dep], command_policy=fixture_policy)
bad_dep = copy.deepcopy(dep_command); bad_dep['arguments'].insert(1, '-Wno-everything')
commandcase('tracked_dependency_new_blanket_suppression', [*inventory, bad_dep], command_policy=fixture_policy)
bad_dep = copy.deepcopy(dep_command); bad_dep['arguments'].insert(1, gate.DEMOTION)
commandcase('tracked_dependency_demotion', [*inventory, bad_dep], command_policy=fixture_policy)
bad_dep = copy.deepcopy(dep_command); bad_dep['arguments'].remove('-Werror')
commandcase('tracked_dependency_missing_werror', [*inventory, bad_dep], command_policy=fixture_policy)
test_command = command(test_source)
test_command['arguments'] = [a for a in test_command['arguments'] if a not in ('-Wall', '-Wextra')]
commandcase('native_unit_test_without_private_warning_interface', [*inventory, test_command], 'PASS')
bad_test = copy.deepcopy(test_command); bad_test['arguments'].insert(1, '-w')
commandcase('unit_test_warnings_disabled', [*inventory, bad_test], command_policy=fixture_policy)
bad_test = copy.deepcopy(test_command); bad_test['arguments'].insert(1, '-Wno-unused-variable')
commandcase('unit_test_extra_suppression', [*inventory, bad_test])
bad = copy.deepcopy(inventory); bad[2]['arguments'].remove('-Wall')
commandcase('game_source_missing_native_wall', bad)
run('absent_dependency_checkout', 'REJECT', lambda: gate.verify_identity(ac, policy))

report = dict(snapshot=str(snapshot), verifier_sha256=hashlib.sha256((snapshot / 'verify_build.py').read_bytes()).hexdigest(),
              count=len(results), mismatches=[r for r in results if not r['matches']], results=results)
(snapshot / 'independent-results.json').write_text(json.dumps(report, indent=2) + '\n')
print(json.dumps({k:v for k,v in report.items() if k != 'results'}, indent=2))
