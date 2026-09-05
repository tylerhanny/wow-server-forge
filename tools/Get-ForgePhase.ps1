param(
    [DateTimeOffset] $AtUtc = [DateTimeOffset]::UtcNow
)

# Read-only Director aid. The recorded clock remains authoritative.
$ErrorActionPreference = 'Stop'
$forgeRoot = Split-Path -Parent $PSScriptRoot
$runStatePath = Join-Path $forgeRoot 'RUN_STATE.md'
$stateText = Get-Content -LiteralPath $runStatePath -Raw -Encoding utf8
$fields = @{}
foreach ($match in [regex]::Matches($stateText, '(?m)^([A-Z_]+)=([^\r\n]+)\r?$')) {
    if ($fields.ContainsKey($match.Groups[1].Value)) {
        throw "Duplicate run-state field: $($match.Groups[1].Value)"
    }
    $fields[$match.Groups[1].Value] = $match.Groups[2].Value.Trim()
}

$timeKeys = @('START_UTC', 'FEATURE_FREEZE_UTC', 'CANDIDATE_HANDOFF_UTC', 'OWNER_TESTING_START_UTC', 'OWNER_TESTING_END_UTC', 'HARD_DEADLINE_UTC')
if ($fields['STATUS'] -eq 'AWAITING_CURRENT_CONTROL') {
    if ($fields['START_UTC'] -ne 'UNSET') { throw 'Preserve an already recorded implementation start.' }
    $fixedDeadline = [DateTimeOffset]::Parse($fields['HARD_DEADLINE_UTC'])
    [ordered]@{
        Status = 'AWAITING_CURRENT_CONTROL'
        RequiredPhase = $(if ($AtUtc -ge $fixedDeadline) { 'COMPLETE' } else { 'SETUP' })
        RecordedPhase = $fields['CURRENT_PHASE']
        CurrentUtc = $AtUtc.ToUniversalTime().ToString('o')
        ImplementationStarted = $false
        CalendarDeadlineActive = $true
        HardDeadlineUtc = $fixedDeadline.ToString('o')
        RemainingHours = [math]::Max([double]0, [math]::Round(($fixedDeadline - $AtUtc).TotalHours, 3))
        NextAction = 'Finish current attempt; start approved implementation after any terminal result, with validation concurrent.'
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

$receipt = [DateTimeOffset]::Parse($fields['DIRECTIVE_RECEIVED_UTC'])
if ($times['HARD_DEADLINE_UTC'] -gt $receipt.AddHours(36) -or
    $times['START_UTC'] -lt $receipt -or
    $times['FEATURE_FREEZE_UTC'] -ne $times['HARD_DEADLINE_UTC'].AddHours(-12) -or
    $times['CANDIDATE_HANDOFF_UTC'] -ne $times['HARD_DEADLINE_UTC'].AddHours(-6) -or
    $times['OWNER_TESTING_START_UTC'] -ne $times['CANDIDATE_HANDOFF_UTC'] -or
    $times['OWNER_TESTING_END_UTC'] -ne $times['HARD_DEADLINE_UTC']) {
    throw 'Invalid fixed deadline or protected owner-testing window; do not reset or extend the ceiling.'
}

$phase = if ($AtUtc -ge $times['HARD_DEADLINE_UTC']) { 'COMPLETE' }
    elseif ($AtUtc -ge $times['CANDIDATE_HANDOFF_UTC']) { 'OWNER_TESTING' }
    elseif ($AtUtc -ge $times['FEATURE_FREEZE_UTC']) { 'FEATURE_FREEZE' }
    elseif ($AtUtc -ge $times['START_UTC']) { 'BUILD' }
    else { throw 'Recorded START is in the future; do not invent an earlier phase.' }

[ordered]@{
    Status = $fields['STATUS']
    RequiredPhase = $phase
    RecordedPhase = $fields['CURRENT_PHASE']
    StateUpdateRequired = ($phase -ne $fields['CURRENT_PHASE'])
    CurrentUtc = $AtUtc.ToUniversalTime().ToString('o')
    ClockStarted = $true
    ImplementationStarted = $true
    DeadlineBasis = $fields['DEADLINE_BASIS']
    DirectiveReceivedUtc = $receipt.ToString('o')
    StartUtc = $times['START_UTC'].ToString('o')
    FeatureFreezeUtc = $times['FEATURE_FREEZE_UTC'].ToString('o')
    CandidateHandoffUtc = $times['CANDIDATE_HANDOFF_UTC'].ToString('o')
    OwnerTestingStartUtc = $times['OWNER_TESTING_START_UTC'].ToString('o')
    OwnerTestingEndUtc = $times['OWNER_TESTING_END_UTC'].ToString('o')
    HardDeadlineUtc = $times['HARD_DEADLINE_UTC'].ToString('o')
    RemainingHours = [math]::Max([double]0, [math]::Round(($times['HARD_DEADLINE_UTC'] - $AtUtc).TotalHours, 3))
    NewProjectsAllowed = ($phase -eq 'BUILD' -and $fields['PRIMARY_MODULES_INDEPENDENTLY_ACCEPTED'] -eq 'YES' -and $fields['ADDITIONAL_PROJECT_WINDOW_REVIEW'] -eq 'PASS')
    FeatureImplementationAllowed = ($phase -eq 'BUILD')
    ExistingScopeCompletionAllowed = ($phase -in @('BUILD', 'FEATURE_FREEZE'))
    OwnerFeedbackFixesAllowed = ($phase -ne 'COMPLETE')
    ReserveCapacityForOwnerFeedback = ($phase -eq 'OWNER_TESTING')
    DeliverReadyModulesImmediately = $true
} | ConvertTo-Json
