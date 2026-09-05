// SPDX-License-Identifier: GPL-2.0-or-later
#ifndef STORMWRIGHT_RULES_H
#define STORMWRIGHT_RULES_H

#include <array>
#include <cstddef>
#include <cstdint>

namespace Stormwright
{
enum class Phase { Idle, Waiting, Tracking, Locked, Resolving };
enum class Event { None, Mark, Lock, Impact, Timeout };
enum class Spend { Discharge, Ground };

struct Preset
{
    char const* name;
    std::uint32_t trackingMs;
    std::uint32_t lockedMs;
    std::uint32_t recoveryMs;
    std::uint32_t cooldownMs;
    std::uint32_t healPercent;
    std::uint32_t damagePercent;
};

inline constexpr std::array<Preset, 3> Presets{{
    { "Normal", 4000, 2000, 18000, 30000, 30, 6 },
    { "Surge", 3500, 2000, 16500, 31000, 28, 6 },
    { "Tempest", 3000, 1800, 15200, 32000, 26, 6 }
}};
inline constexpr std::uint32_t TimeLimitMs = 12 * 60 * 1000;
inline constexpr std::uint32_t VulnerabilityMs = 8000;
inline constexpr std::uint32_t MaximumWard = 3;

struct Rod
{
    bool charged = false;
    std::uint64_t coolingUntil = 0;
};

// The rules own all charge/ward transitions. World positions and living-player
// ownership are checked by the controller before it calls Resolve or Activate.
class Rules
{
public:
    constexpr bool Begin(std::size_t preset)
    {
        if (Active() || preset >= Presets.size())
            return false;
        *this = Rules{};
        _preset = preset;
        _phase = Phase::Waiting;
        _next = 12000; // Time to leave the registrar and read the first mark.
        return true;
    }

    constexpr Event Tick(std::uint32_t diff)
    {
        if (!Active())
            return Event::None;
        _elapsed += diff;
        if (_elapsed >= TimeLimitMs)
            return Event::Timeout;
        if (_elapsed < _next)
            return Event::None;

        // Advance at most one visible phase per tick. A delayed server update
        // must not collapse the player's entire lock-and-escape interval.
        switch (_phase)
        {
            case Phase::Waiting:
                _phase = Phase::Tracking;
                _next = _elapsed + Settings().trackingMs;
                return Event::Mark;
            case Phase::Tracking:
                _phase = Phase::Locked;
                _next = _elapsed + Settings().lockedMs;
                return Event::Lock;
            case Phase::Locked:
                _phase = Phase::Resolving;
                return Event::Impact;
            default:
                return Event::None;
        }
    }

    // A value outside [0,3) is a miss. A cooling/charged rod cannot catch again.
    constexpr bool Resolve(std::size_t rod)
    {
        if (_phase != Phase::Resolving)
            return false;
        bool const caught = Ready(rod);
        if (caught)
            _rods[rod].charged = true;
        else
        {
            ++_misses;
            if (_ward != 0)
                --_ward;
        }
        _phase = Phase::Waiting;
        _next = _elapsed + Settings().recoveryMs;
        return caught;
    }

    constexpr bool Activate(std::size_t rod, Spend action, bool pilotInjured)
    {
        if (!Active() || _ward == 0 || rod >= _rods.size() || !_rods[rod].charged)
            return false;
        if (action == Spend::Ground && _ward == MaximumWard && !pilotInjured)
            return false;
        // Consume before awarding effects. Duplicate gossip cannot spend twice.
        _rods[rod].charged = false;
        _rods[rod].coolingUntil = _elapsed + Settings().cooldownMs;
        if (action == Spend::Ground)
        {
            if (_ward < MaximumWard)
                ++_ward;
            ++_grounds;
        }
        else
        {
            _vulnerableUntil = _elapsed + VulnerabilityMs;
            ++_discharges;
        }
        return true;
    }

    constexpr bool Active() const { return _phase != Phase::Idle; }
    constexpr bool Ready(std::size_t rod) const
    {
        return Active() && rod < _rods.size() && !_rods[rod].charged &&
            _rods[rod].coolingUntil <= _elapsed;
    }
    constexpr bool Charged(std::size_t rod) const { return rod < _rods.size() && _rods[rod].charged; }
    constexpr bool Vulnerable() const { return Active() && _elapsed < _vulnerableUntil; }
    constexpr std::uint32_t CoolingSeconds(std::size_t rod) const
    {
        if (rod >= _rods.size() || _rods[rod].coolingUntil <= _elapsed)
            return 0;
        return static_cast<std::uint32_t>((_rods[rod].coolingUntil - _elapsed + 999) / 1000);
    }
    constexpr void End() { _phase = Phase::Idle; }
    constexpr Phase CurrentPhase() const { return _phase; }
    constexpr Preset const& Settings() const { return Presets[_preset]; }
    constexpr std::uint64_t Elapsed() const { return _elapsed; }
    constexpr std::uint32_t Ward() const { return _ward; }
    constexpr std::uint32_t Misses() const { return _misses; }
    constexpr std::uint32_t Grounds() const { return _grounds; }
    constexpr std::uint32_t Discharges() const { return _discharges; }

private:
    Phase _phase = Phase::Idle;
    std::size_t _preset = 0;
    std::uint64_t _elapsed = 0;
    std::uint64_t _next = 0;
    std::uint64_t _vulnerableUntil = 0;
    std::uint32_t _ward = MaximumWard;
    std::uint32_t _misses = 0;
    std::uint32_t _grounds = 0;
    std::uint32_t _discharges = 0;
    std::array<Rod, 3> _rods{};
};
}
#endif
