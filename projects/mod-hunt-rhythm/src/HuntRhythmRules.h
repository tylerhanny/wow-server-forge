#ifndef MOD_HUNT_RHYTHM_RULES_H
#define MOD_HUNT_RHYTHM_RULES_H

#include <algorithm>
#include <cstdint>
#include <limits>

namespace HuntRhythm
{
struct Settings
{
    bool enabled = true;
    std::uint32_t windowSeconds = 60;
    std::uint32_t stepPercent = 2;
    std::uint32_t maxBonusPercent = 10;
};

constexpr Settings Normalize(bool enabled, std::int32_t window, std::int32_t step, std::int32_t cap)
{
    return {enabled, static_cast<std::uint32_t>(std::clamp(window, 15, 300)),
            static_cast<std::uint32_t>(std::clamp(step, 1, 5)),
            static_cast<std::uint32_t>(std::clamp(cap, 1, 20))};
}

// Presence in the session store is the opt-in. No Player pointer is retained.
struct Chain
{
    std::uint32_t kills = 0;
    std::uint64_t lastKillMs = 0;
    bool bonusDeclined = false;
};

constexpr bool Expire(Chain& chain, std::uint64_t nowMs, Settings const& settings)
{
    if (chain.kills && (nowMs < chain.lastKillMs ||
        nowMs - chain.lastKillMs >= std::uint64_t(settings.windowSeconds) * 1000))
    {
        chain = {};
        return true;
    }
    return false;
}

constexpr std::uint32_t Percent(std::uint32_t kills, Settings const& settings)
{
    return kills ? static_cast<std::uint32_t>(std::min<std::uint64_t>(
        std::uint64_t(kills - 1) * settings.stepPercent, settings.maxBonusPercent)) : 0;
}

constexpr std::uint32_t NextKills(std::uint32_t kills)
{
    return kills == std::numeric_limits<std::uint32_t>::max() ? kills : kills + 1;
}

constexpr void Advance(Chain& chain, std::uint64_t nowMs, Settings const& settings)
{
    Expire(chain, nowMs, settings);
    chain.kills = NextKills(chain.kills);
    chain.lastKillMs = nowMs;
}

constexpr std::uint32_t RemainingSeconds(Chain const& chain, std::uint64_t nowMs, Settings const& settings)
{
    if (!chain.kills || nowMs < chain.lastKillMs)
        return 0;
    std::uint64_t const windowMs = std::uint64_t(settings.windowSeconds) * 1000;
    std::uint64_t const elapsed = nowMs - chain.lastKillMs;
    return elapsed >= windowMs ? 0 : static_cast<std::uint32_t>((windowMs - elapsed + 999) / 1000);
}

struct Award
{
    std::uint32_t amount;
    std::uint32_t added;
    bool declined;
};

constexpr Award AddBonus(std::uint32_t base, std::uint32_t percent, std::uint32_t currentXp)
{
    std::uint64_t const added = std::uint64_t(base) * percent / 100;
    if (!added)
        return {base, 0, false};

    std::uint64_t const candidate = std::uint64_t(base) + added;
    constexpr std::uint64_t limit = std::numeric_limits<std::uint32_t>::max();
    if (candidate > limit)
        return {base, 0, true};

    // The pinned core rounds through float, even outside favored areas. Match its
    // worst-case +5% expression before bounding RAF (3x total) and current XP.
    // Partial play time only reduces this; rested adds at most 1x instead of 2x.
    float const favored = static_cast<float>(candidate) * (1.0f + 0.05f);
    std::uint64_t const downstream = static_cast<std::uint64_t>(favored);
    if (std::uint64_t(currentXp) + 3 * downstream > limit)
        return {base, 0, true};

    return {static_cast<std::uint32_t>(candidate), static_cast<std::uint32_t>(added), false};
}
}

#endif
