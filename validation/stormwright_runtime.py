#!/usr/bin/env python3
"""Existing Stormwright OnStartup evidence, using the already-built disposable server.

This supplements the unchanged official dry-runs and upstream unit tests. It is
not a client, encounter-playthrough, pathfinding or Playerbots competence test.
"""
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
import subprocess
import time
import zipfile


URL = 'https://github.com/wowgaming/client-data/releases/download/v20.0/Data.zip'
SHA256 = 'a3d4df635ae6c2c8f08052c32a79e0f806955150ad36b014a823dd08a32a4610'
EVIDENCE = Path('evidence')
DIST = Path('ac/env/dist')


def main():
    if os.environ.get('GITHUB_ACTIONS') != 'true' or os.environ.get('PROJECT') != 'mod-stormwright':
        raise SystemExit('This check is only for the disposable Stormwright Actions candidate.')
    archive = Path(os.environ['RUNNER_TEMP']) / 'forge-public-map-data-v20.zip'
    subprocess.run(['curl', '--fail', '--location', '--retry', '2', '--max-time', '600',
                    '--output', str(archive), URL], check=True)
    with archive.open('rb') as source:
        actual_hash = hashlib.file_digest(source, 'sha256').hexdigest()
    if actual_hash != SHA256:
        raise SystemExit('Public map-data archive identity mismatch; no data extracted.')
    # Keep the original recorded ac-data DBC checkout. Add extracted terrain only.
    extracted = []
    data_root = (DIST / 'data').resolve()
    with zipfile.ZipFile(archive) as bundle:
        for item in bundle.infolist():
            path = PurePosixPath(item.filename)
            if not path.parts or path.parts[0] not in ('maps', 'vmaps', 'mmaps'):
                continue
            if path.is_absolute() or '..' in path.parts or '\\' in item.filename:
                raise SystemExit('Invalid archive path')
            bundle.extract(item, data_root)
            if not item.is_dir():
                extracted.append(item.filename)
    archive.unlink()  # Exact disposable download only; no recursive deletion.
    for name in ('maps/0014338.map', 'maps/0014339.map',
                 'vmaps/001.vmtree', 'mmaps/0014338.mmtile', 'mmaps/0014339.mmtile'):
        if not (data_root / name).is_file():
            raise SystemExit(f'Missing required Stormwright terrain entry: {name}')
    (EVIDENCE / 'stormwright-runtime-data.json').write_text(json.dumps({
        'url': URL, 'sha256': actual_hash, 'extracted_files': len(extracted),
        'folders': ['maps', 'vmaps', 'mmaps'], 'dbc': 'original recorded ac-data checkout',
    }, indent=2) + '\n')

    config = DIST / 'etc/worldserver.conf'
    text = config.read_text()
    settings = {'BindIP': '"127.0.0.1"', 'Console.Enable': '1', 'Ra.Enable': '0',
                'SOAP.Enabled': '0', 'Cluster.Enabled': '0',
                'Logger.module': '4,Console Server'}
    for key, value in settings.items():
        text, count = re.subn(r'^' + re.escape(key) + r'\s*=.*$',
                             f'{key} = {value}', text, flags=re.MULTILINE)
        if count != 1:
            raise SystemExit(f'Expected one installed runtime setting: {key}')
    config.write_text(text)
    (EVIDENCE / 'stormwright-runtime-fixture.conf').write_text(
        ''.join(f'{key} = {value}\n' for key, value in settings.items()))

    # The normal updater already applied module SQL during the required dry-run.
    query = """SELECT entry, ScriptName FROM creature_template
WHERE entry BETWEEN 910900 AND 910904 ORDER BY entry;
SELECT CreatureID, CreatureDisplayID FROM creature_template_model
WHERE CreatureID BETWEEN 910900 AND 910904 ORDER BY CreatureID;
SELECT ID FROM npc_text WHERE ID=910900;"""
    rows = subprocess.check_output(['mysql', '--host=127.0.0.1', '--user=root',
        '--password=root', '--batch', '--skip-column-names', 'acore_world', '--execute', query], text=True)
    (EVIDENCE / 'stormwright-installed-sql.tsv').write_text(rows)
    expected = ['910900\tnpc_stormwright_registrar', '910901\tnpc_stormwright_rod',
        '910902\tnpc_stormwright_enemy', '910903\tnpc_stormwright_enemy',
        '910904\tnpc_stormwright_marker', '910900\t5443', '910901\t17856',
        '910902\t26382', '910903\t23349', '910904\t26753', '910900']
    if rows.splitlines() != expected:
        raise SystemExit('Installed Stormwright owned SQL does not match reviewed candidate requirements.')

    log_path = EVIDENCE / 'stormwright-worldserver-running.log'
    began = time.monotonic()
    observed_at = None
    sent_exit = False
    with log_path.open('w') as log:
        process = subprocess.Popen([str(DIST / 'bin/worldserver')], stdin=subprocess.PIPE,
                                   stdout=log, stderr=subprocess.STDOUT, text=True)
        try:
            while process.poll() is None:
                elapsed = time.monotonic() - began
                if elapsed > 300:
                    raise RuntimeError('Stormwright normal-startup/exit exceeded the existing five-minute bound.')
                output = log_path.read_text(errors='replace')
                if observed_at is None and re.search(
                    r'STORMWRIGHT_REGISTRAR spawned=true map=1 x=-6250 y=-3790 derived_z=', output):
                    observed_at = time.monotonic()
                if observed_at is not None and not sent_exit and time.monotonic() - observed_at >= 5:
                    process.stdin.write('server info\nserver exit\n')
                    process.stdin.flush()
                    sent_exit = True
                time.sleep(0.25)
            if process.returncode != 0 or not sent_exit:
                raise RuntimeError(f'Normal startup/console shutdown failed: exit={process.returncode}')
        finally:
            if process.poll() is None:
                process.terminate()
                try:
                    process.wait(timeout=30)
                except subprocess.TimeoutExpired:
                    process.kill()
                    process.wait(timeout=10)
            process.stdin.close()
    output = log_path.read_text(errors='replace')
    if 'Halting process...' not in output or 'STORMWRIGHT_SITE_UNAVAILABLE' in output:
        raise SystemExit('Normal startup/clean shutdown evidence is incomplete.')
    errors = DIST / 'logs/Errors.log'
    if errors.exists() and errors.stat().st_size:
        raise SystemExit('Errors.log contains normal-startup/runtime errors; retained in artifact.')
    (EVIDENCE / 'stormwright-runtime-verdict.json').write_text(json.dumps({
        'result': 'PASS', 'normal_startup': True, 'registrar_spawn_observed': True,
        'owned_sql_verified': True, 'console_shutdown_exit': process.returncode,
        'client_gameplay_navigation_bot_competence': 'NOT_TESTED',
    }, indent=2) + '\n')
    print('PASS: installed Stormwright SQL, actual registrar OnStartup, bounded normal server loop and clean console shutdown. Gameplay remains untested.')


if __name__ == '__main__':
    main()
