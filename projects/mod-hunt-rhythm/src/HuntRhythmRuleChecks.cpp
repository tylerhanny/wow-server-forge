#include "HuntRhythmRules.h"

// Focused compile-time checks exercise the actual rule functions with no test
// framework, server mocks, test bypasses, or runtime startup side effects.
namespace
{
constexpr HuntRhythm::Settings defaults{};
static_assert(HuntRhythm::Percent(1, defaults) == 0);
static_assert(HuntRhythm::Percent(2, defaults) == 2);
static_assert(HuntRhythm::Percent(6, defaults) == 10);
static_assert(HuntRhythm::Percent(1000, defaults) == 10);
static_assert(HuntRhythm::AddBonus(101, 2, 0).amount == 103);
static_assert(HuntRhythm::AddBonus(1, 20, 0).added == 0);
static_assert(HuntRhythm::AddBonus(1000, 10, 0).amount == 1100);
static_assert(HuntRhythm::AddBonus(0xFFFFFFFFu, 20, 0).declined);
static_assert(HuntRhythm::AddBonus(1000, 10, 0xFFFFFFFFu).declined);
static_assert(HuntRhythm::AddBonus(1400000000, 10, 0).declined);
static_assert(HuntRhythm::AddBonus(1400000000, 10, 0).amount == 1400000000);
static_assert(HuntRhythm::NextKills(0xFFFFFFFFu) == 0xFFFFFFFFu);
static_assert(HuntRhythm::Normalize(true, -1, 0, 99).windowSeconds == 15);
static_assert(HuntRhythm::Normalize(true, 999, 99, -1).windowSeconds == 300);
static_assert(HuntRhythm::Normalize(false, 60, 2, 10).enabled == false);
static_assert(HuntRhythm::Normalize(true, 60, 0, 99).stepPercent == 1);
static_assert(HuntRhythm::Normalize(true, 60, 99, 0).maxBonusPercent == 1);

constexpr bool CheckWindow()
{
    HuntRhythm::Chain chain;
    HuntRhythm::Advance(chain, 1000, defaults);
    if (chain.kills != 1 || HuntRhythm::Expire(chain, 60999, defaults))
        return false;
    if (HuntRhythm::RemainingSeconds(chain, 60999, defaults) != 1)
        return false;
    if (!HuntRhythm::Expire(chain, 61000, defaults) || chain.kills != 0)
        return false;
    HuntRhythm::Advance(chain, 61000, defaults);
    HuntRhythm::Advance(chain, 62000, defaults);
    if (chain.kills != 2 || HuntRhythm::RemainingSeconds(chain, 62000, defaults) != 60)
        return false;
    HuntRhythm::Advance(chain, 122000, defaults);
    return chain.kills == 1 && HuntRhythm::Expire(chain, 121999, defaults);
}
static_assert(CheckWindow());
}
