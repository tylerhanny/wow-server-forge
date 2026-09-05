// SPDX-License-Identifier: GPL-2.0-or-later
#include "StormwrightRules.h"

namespace Stormwright
{
namespace
{
constexpr bool Strike(Rules& rules, std::size_t rod, bool first = false)
{
    return rules.Tick(first ? 12000 : rules.Settings().recoveryMs) == Event::Mark &&
        rules.Tick(rules.Settings().trackingMs) == Event::Lock &&
        rules.Tick(rules.Settings().lockedMs) == Event::Impact &&
        rules.Resolve(rod) == (rod < 3);
}

constexpr bool RecoveryAndRetry()
{
    for (std::size_t preset = 0; preset < Presets.size(); ++preset)
    {
        Rules rules;
        if (rules.Begin(Presets.size()) || !rules.Begin(preset) || rules.Begin(preset) ||
            rules.Activate(0, Spend::Ground, true) || rules.Resolve(0) || !Strike(rules, 0, true))
            return false;
        if (rules.Activate(0, Spend::Ground, false) || !rules.Charged(0) ||
            !rules.Activate(0, Spend::Ground, true) || rules.Grounds() != 1 || rules.Ward() != 3 ||
            rules.Activate(0, Spend::Ground, true) || rules.Ready(0) || rules.CoolingSeconds(0) == 0)
            return false;
        if (!Strike(rules, 1) || !rules.Activate(1, Spend::Discharge, false) || !rules.Vulnerable() ||
            rules.Discharges() != 1 || rules.Tick(VulnerabilityMs) != Event::None || rules.Vulnerable())
            return false;
        rules.End();
        if (rules.Activate(1, Spend::Discharge, false) || !rules.Begin(preset) || rules.Elapsed() != 0 ||
            rules.Ward() != 3 || rules.Discharges() != 0 || !Strike(rules, 3, true) || !Strike(rules, 0) ||
            rules.Ward() != 2 || !rules.Activate(0, Spend::Ground, false) || rules.Ward() != 3)
            return false;
        if (!Strike(rules, 3) || !Strike(rules, 3) || !Strike(rules, 3) || rules.Ward() != 0 ||
            rules.Activate(0, Spend::Ground, true))
            return false;
    }
    return true;
}

constexpr bool VisiblePhasesSurviveLag()
{
    Rules rules;
    return rules.Begin(0) && rules.Tick(20000) == Event::Mark && rules.Tick(10000) == Event::Lock &&
        rules.Tick(1) == Event::None && rules.Tick(1999) == Event::Impact && rules.Resolve(0) &&
        rules.Tick(TimeLimitMs) == Event::Timeout;
}

static_assert(RecoveryAndRetry(), "Every preset must retain solo recovery, finite charge, failure and clean retry");
static_assert(VisiblePhasesSurviveLag(), "A delayed tick must not erase the pilot's escape window or time cap");
}
}
