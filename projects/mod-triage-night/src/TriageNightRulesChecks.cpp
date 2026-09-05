// SPDX-License-Identifier: GPL-2.0-or-later
#include "TriageNightRules.h"
#include <initializer_list>

namespace TriageNight
{
namespace
{
constexpr bool CompleteShift()
{
    for (bool veteran : {false, true})
        for (std::size_t rotation = 0; rotation < PatientCount; ++rotation)
        {
            Rules rules;
            if (!rules.Begin(veteran, rotation) || rules.Begin(false, 0) || rules.Stabilize(0))
                return false;
            std::uint32_t rounds = 0;
            std::uint32_t breaks = 0;
            std::uint32_t warnings = 0;
            std::uint32_t injurySteps = 0;
            std::array<std::uint32_t, PatientCount> expectedBurst{};
            for (std::uint32_t seconds = 1; seconds <= 275; ++seconds)
            {
                Step const step = rules.Tick(1000);
                if (step.event == Event::RoundStarted)
                    ++rounds;
                if (step.event == Event::BreakStarted)
                    ++breaks;
                if (step.warning < PatientCount)
                {
                    ++warnings;
                    expectedBurst[step.warning] = seconds + 4;
                }
                bool injury = false;
                for (std::size_t patient = 0; patient < PatientCount; ++patient)
                {
                    injury = injury || step.injury[patient] != 0;
                    if (expectedBurst[patient] == seconds && step.injury[patient] < 4800)
                        return false;
                }
                if (injury)
                    ++injurySteps;
                if (seconds < 275 && step.event == Event::Complete)
                    return false;
            }
            if (rules.CurrentPhase() != Phase::Complete || rounds != 5 || breaks != 4 ||
                warnings != 9 || injurySteps != 225 || rules.Stabilize(0) ||
                rules.Tick(1000).event != Event::None || !rules.Begin(veteran, rotation) ||
                rules.Charges() != 2 || rules.ElapsedMs() != 0)
                return false;
        }
    return true;
}

constexpr bool FiniteRescueAndTime()
{
    Rules rules;
    rules.Begin(false, 0);
    for (std::uint32_t i = 0; i < 10; ++i)
        rules.Tick(1000);
    if (rules.Stabilize(PatientCount) || !rules.Stabilize(0) || rules.Charges() != 1 || rules.Stabilize(0))
        return false;
    for (std::uint32_t i = 0; i < 5; ++i)
        if (rules.Tick(1000).injury[0] != 0)
            return false;
    if (rules.Tick(1000).injury[0] == 0 || !rules.Stabilize(1) || rules.Charges() != 0 || rules.Stabilize(2))
        return false;
    rules.End();
    if (rules.Stabilize(0) || rules.Tick(1000).event != Event::None || !rules.Begin(false, 0))
        return false;
    // A late update preserves the briefing rather than silently fast-forwarding.
    if (rules.Tick(9000).event != Event::None || rules.Second() != 1 || rules.ElapsedMs() != 9000)
        return false;
    return rules.Tick(TimeLimitMs).event == Event::Timeout && !rules.Active();
}

static_assert(CompleteShift(), "Every preset/role rotation retains all five rounds, four finite breaks and warned bursts");
static_assert(FiniteRescueAndTime(), "Stabilization is finite, cannot stack, expires, and resets only for a fresh shift");
}
}
