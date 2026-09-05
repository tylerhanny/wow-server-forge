// SPDX-License-Identifier: GPL-2.0-or-later
#include "../src/StormwrightRules.h"
#include <cstdlib>
#include <iostream>

namespace
{
void Require(bool condition, char const* description)
{
    if (!condition)
    {
        std::cerr << "FAIL: " << description << '\n';
        std::exit(EXIT_FAILURE);
    }
}

void Catch(Stormwright::Rules& rules, std::size_t rod, bool first = false)
{
    using namespace Stormwright;
    Require(rules.Tick(first ? 12000 : rules.Settings().recoveryMs) == Event::Mark, "mark starts");
    Require(rules.Tick(rules.Settings().trackingMs) == Event::Lock, "mark locks");
    Require(rules.Tick(rules.Settings().lockedMs) == Event::Impact, "locked mark impacts");
    Require(rules.Resolve(rod) == (rod < 3), "catch or intentional miss resolves");
}
}

int main()
{
    using namespace Stormwright;
    for (std::size_t preset = 0; preset < Presets.size(); ++preset)
    {
        Rules rules;
        Require(!rules.Begin(Presets.size()), "invalid preset rejected");
        Require(rules.Begin(preset), "preset starts");
        Require(!rules.Begin(preset), "active run cannot restart");
        Require(!rules.Activate(0, Spend::Discharge, false), "empty capacitor cannot discharge");
        Require(!rules.Resolve(0), "catch cannot be invented outside impact");
        Catch(rules, 0, true);
        Require(rules.Charged(0) && !rules.Ready(0), "stored charge blocks repeated catch");
        Require(!rules.Activate(0, Spend::Ground, false) && rules.Charged(0), "full health/ward keeps charge");
        Require(rules.Activate(0, Spend::Ground, true), "injured solo pilot can ground at full ward");
        Require(rules.Grounds() == 1 && rules.Ward() == 3, "ground recorded without ward overflow");
        Require(!rules.Activate(0, Spend::Ground, true), "duplicate gossip cannot heal twice");
        Require(!rules.Ready(0) && rules.CoolingSeconds(0) > 0, "spent rod cools");
        Catch(rules, 1);
        Require(rules.Activate(1, Spend::Discharge, false), "offense choice works");
        Require(rules.Vulnerable() && rules.Discharges() == 1, "discharge opens armor");
        Require(rules.Tick(VulnerabilityMs) == Event::None && !rules.Vulnerable(), "armor window expires");
        Require(!rules.Activate(7, Spend::Ground, true), "invalid rod rejected");
        rules.End();
        Require(!rules.Activate(1, Spend::Discharge, false), "terminal run rejects input");
        Require(rules.Begin(preset) && rules.Elapsed() == 0 && rules.Ward() == 3 && rules.Grounds() == 0,
            "retry resets all previous run resources");
        Catch(rules, 3, true);
        Catch(rules, 0);
        Require(rules.Ward() == 2 && rules.Misses() == 1, "miss costs ward");
        Require(rules.Activate(0, Spend::Ground, false) && rules.Ward() == 3, "uninjured pilot can repair ward");
        Catch(rules, 3);
        Catch(rules, 3);
        Catch(rules, 3);
        Require(rules.Ward() == 0 && !rules.Activate(0, Spend::Ground, true), "ward failure cannot be revived by gossip");
    }
    Rules lag;
    Require(lag.Begin(0), "lag scenario starts");
    Require(lag.Tick(20000) == Event::Mark, "lag does not skip tracking phase");
    Require(lag.Tick(10000) == Event::Lock, "lag does not skip escape phase");
    Require(lag.Tick(1) == Event::None, "full escape interval survives late tick");
    Require(lag.Tick(1999) == Event::Impact, "escape interval completes");
    Require(lag.Resolve(0), "lagged catch resolves");
    Require(lag.Tick(TimeLimitMs) == Event::Timeout, "hard time cap remains active");
    std::cout << "PASS: all presets, ownership-independent rules, recovery, duplicate input, retry, lag, time cap\n";
}
