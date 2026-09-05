// SPDX-License-Identifier: GPL-2.0-or-later
#ifndef TRIAGE_NIGHT_RULES_H
#define TRIAGE_NIGHT_RULES_H

#include <array>
#include <cstddef>
#include <cstdint>

namespace TriageNight
{
constexpr std::size_t PatientCount = 3;
constexpr std::uint32_t PatientHealth = 12000;
constexpr std::uint32_t TimeLimitMs = 360000;
constexpr std::uint32_t StabilizationMs = 6000;
constexpr std::uint32_t RoundSeconds = 45;
constexpr std::uint32_t BreakSeconds = 10;
constexpr std::uint32_t RoundCount = 5;

enum class Phase { Idle, Briefing, Round, Break, Complete, Ended };
enum class Event { None, Injury, RoundStarted, BreakStarted, Complete, Timeout };

struct Step
{
    Event event = Event::None;
    std::array<std::uint32_t, PatientCount> injury{};
    std::size_t warning = PatientCount;
};

class Rules
{
public:
    constexpr bool Begin(bool veteran, std::size_t rotation)
    {
        if (Active())
            return false;
        *this = Rules{};
        _phase = Phase::Briefing;
        _veteran = veteran;
        _rotation = rotation % PatientCount;
        return true;
    }

    constexpr bool Active() const
    {
        return _phase == Phase::Briefing || _phase == Phase::Round || _phase == Phase::Break;
    }
    constexpr Phase CurrentPhase() const { return _phase; }
    constexpr bool Veteran() const { return _veteran; }
    constexpr std::uint32_t Round() const { return _round + 1; }
    constexpr std::uint32_t Second() const { return _second; }
    constexpr std::uint32_t Charges() const { return _charges; }
    constexpr std::uint32_t ElapsedMs() const { return _elapsedMs; }
    constexpr std::size_t Patient(std::size_t role) const { return (role + _rotation + _round) % PatientCount; }
    constexpr std::uint32_t PausedSeconds(std::size_t patient) const
    {
        return patient < PatientCount && _pausedUntil[patient] > _elapsedMs ?
            (_pausedUntil[patient] - _elapsedMs + 999) / 1000 : 0;
    }
    constexpr bool Stabilize(std::size_t patient)
    {
        if (_phase != Phase::Round || patient >= PatientCount || !_charges || PausedSeconds(patient))
            return false;
        --_charges;
        _pausedUntil[patient] = _elapsedMs + StabilizationMs;
        return true;
    }
    constexpr void End() { _phase = Phase::Ended; }

    // At most one visible second per update: a delayed update never compresses
    // several injury warnings into one frame. The real elapsed cap still applies.
    constexpr Step Tick(std::uint32_t diff)
    {
        if (!Active())
            return {};
        if (diff >= TimeLimitMs - _elapsedMs)
        {
            _elapsedMs = TimeLimitMs;
            _phase = Phase::Ended;
            return {Event::Timeout, {}, PatientCount};
        }
        _elapsedMs += diff;
        if (diff < _stepMs)
        {
            _stepMs -= diff;
            return {};
        }
        _stepMs = 1000;
        ++_second;
        if (_phase == Phase::Briefing || _phase == Phase::Break)
        {
            if (_second < BreakSeconds)
                return {};
            if (_phase == Phase::Break)
                ++_round;
            _second = 0;
            _phase = Phase::Round;
            return {Event::RoundStarted, {}, PatientCount};
        }

        Step step{Event::Injury, {}, PatientCount};
        std::array<std::uint32_t, PatientCount> roleInjury{};
        std::size_t burstRole = PatientCount;
        std::uint32_t burst = 0;
        switch (_round)
        {
            case 0: roleInjury = {{350, 120, 120}}; break;
            case 1: roleInjury = {{80, 250, 150}}; burstRole = 0; burst = 7200; break;
            case 2: roleInjury = {{450, 450, 80}}; break;
            case 3:
                roleInjury = {{250, 250, 250}};
                burstRole = ((_second + 3) / 12) % PatientCount;
                burst = 4800;
                break;
            default: roleInjury = {{450, 350, 200}}; burstRole = 2; burst = 6200; break;
        }
        if (burstRole < PatientCount)
        {
            if (_second % 12 == 8 && _second + 4 <= RoundSeconds)
            {
                // The rotating-crisis target must match the upcoming impact.
                if (_round == 3)
                    burstRole = ((_second + 4) / 12) % PatientCount;
                step.warning = Patient(burstRole);
            }
            if (_second % 12 == 0)
                roleInjury[burstRole] += burst;
        }
        for (std::size_t role = 0; role < PatientCount; ++role)
        {
            std::size_t const patient = Patient(role);
            if (!PausedSeconds(patient))
                step.injury[patient] = roleInjury[role] * (_veteran ? 135u : 100u) / 100;
        }
        if (_second == RoundSeconds)
        {
            _second = 0;
            if (_round + 1 == RoundCount)
            {
                _phase = Phase::Complete;
                step.event = Event::Complete;
            }
            else
            {
                _phase = Phase::Break;
                step.event = Event::BreakStarted;
            }
        }
        return step;
    }

private:
    Phase _phase = Phase::Idle;
    bool _veteran = false;
    std::size_t _rotation = 0;
    std::uint32_t _round = 0;
    std::uint32_t _second = 0;
    std::uint32_t _charges = 2;
    std::uint32_t _elapsedMs = 0;
    std::uint32_t _stepMs = 1000;
    std::array<std::uint32_t, PatientCount> _pausedUntil{};
};
}
#endif
