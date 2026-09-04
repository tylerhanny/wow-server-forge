param(
    [DateTimeOffset] $AtUtc = [DateTimeOffset]::UtcNow
)

# Read-only Director aid. The recorded clock remains authoritative.
$ErrorActionPreference = 'Stop'
$forgeRoot = Split-Path -Parent $PSScriptRoot
$runStatePath = Join-Path $forgeRoot 'RUN_STATE.md'
$stateText = Get-Content -LiteralPath $runStatePath -Raw
$fields = @{}
foreach ($match in [regex]::Matches($stateText, '(?m)^([A-Z_]+)=([^\r\n]+)\r?$')) {
    if ($fields.ContainsKey($match.Groups[1].Value)) {
        throw "Duplicate run-state field: $($match.Groups[1].Value)"
    }
    $fields[$match.Groups[1].Value] = $match.Groups[2].Value.Trim()
}

$timeKeys = @('START_UTC', 'CONVERGENCE_START_UTC', 'HARVEST_START_UTC', 'HARD_DEADLINE_UTC')
if ($fields['STATUS'] -eq 'ARMED_NOT_STARTED') {
    foreach ($key in $timeKeys) {
        if ($fields[$key] -ne 'UNSET') { throw "An armed sprint must have $key=UNSET." }
    }
    [ordered]@{
        Status = 'ARMED_NOT_STARTED'
        RequiredPhase = 'SETUP'
        RecordedPhase = $fields['CURRENT_PHASE']
        CurrentUtc = $AtUtc.ToUniversalTime().ToString('o')
        ClockStarted = $false
        NextAction = 'Prove both external controls before recording launch.'
    } | ConvertTo-Json
    exit 0
}

if ($fields['STATUS'] -notin @('RUNNING', 'COMPLETE')) {
    throw "Unrecognized run status: $($fields['STATUS'])"
}

$times = @{}
foreach ($key in $timeKeys) {
    $parsed = [DateTimeOffset]::Parse($fields[$key], [Globalization.CultureInfo]::InvariantCulture)
    if ($parsed.Offset -ne [TimeSpan]::Zero) { throw "$key must use UTC." }
    $times[$key] = $parsed
}

foreach ($boundary in @(
    @{ Key = 'CONVERGENCE_START_UTC'; Hours = 24 },
    @{ Key = 'HARVEST_START_UTC'; Hours = 30 },
    @{ Key = 'HARD_DEADLINE_UTC'; Hours = 36 }
)) {
    if ($times[$boundary.Key] -ne $times['START_UTC'].AddHours($boundary.Hours)) {
        throw "Invalid $($boundary.Key): the clock must not be reset or extended."
    }
}

$phase = if ($AtUtc -ge $times['HARD_DEADLINE_UTC']) { 'COMPLETE' }
    elseif ($AtUtc -ge $times['HARVEST_START_UTC']) { 'HARVEST' }
    elseif ($AtUtc -ge $times['CONVERGENCE_START_UTC']) { 'CONVERGENCE' }
    elseif ($AtUtc -ge $times['START_UTC']) { 'BUILD' }
    else { throw 'Recorded START is in the future; do not invent an earlier phase.' }

[ordered]@{
    Status = $fields['STATUS']
    RequiredPhase = $phase
    RecordedPhase = $fields['CURRENT_PHASE']
    StateUpdateRequired = ($phase -ne $fields['CURRENT_PHASE'])
    CurrentUtc = $AtUtc.ToUniversalTime().ToString('o')
    ClockStarted = $true
    StartUtc = $times['START_UTC'].ToString('o')
    HardDeadlineUtc = $times['HARD_DEADLINE_UTC'].ToString('o')
    RemainingHours = [math]::Max(0, [math]::Round(($times['HARD_DEADLINE_UTC'] - $AtUtc).TotalHours, 3))
    NewProjectsAllowed = ($phase -eq 'BUILD')
    ConvergenceRequiresExplicitSmallLowRiskDecision = ($phase -eq 'CONVERGENCE')
    FeatureImplementationAllowed = ($phase -in @('BUILD', 'CONVERGENCE'))
} | ConvertTo-Json
