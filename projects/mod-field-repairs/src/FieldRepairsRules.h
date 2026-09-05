#ifndef FIELD_REPAIRS_RULES_H
#define FIELD_REPAIRS_RULES_H

#include <cstdint>
#include <limits>

namespace FieldRepairs
{
constexpr std::uint64_t ConsentMilliseconds = 30000;

constexpr bool ConsentValid(std::uint64_t expiresAt, std::uint64_t now)
{
    return expiresAt > now;
}

constexpr std::uint64_t ConsentSeconds(std::uint64_t expiresAt, std::uint64_t now)
{
    return ConsentValid(expiresAt, now) ? (expiresAt - now + 999) / 1000 : 0;
}

constexpr bool NonnegativeFinite(float value)
{
    return value >= 0.0f && value <= std::numeric_limits<float>::max();
}

// Only a guard: the core calculates and collects the actual charge. Match its
// multiplication order, double truncation, then float rate conversion exactly.
constexpr bool NativeCostSafe(std::uint32_t maximum, std::uint32_t current,
    std::uint32_t multiplier, float quality, float rate)
{
    if (current > maximum)
        return false;
    if (maximum == current)
        return true;
    if (!NonnegativeFinite(quality) || !NonnegativeFinite(rate))
        return false;

    std::uint64_t const product = static_cast<std::uint64_t>(maximum - current) * multiplier;
    if (product > std::numeric_limits<std::uint32_t>::max())
        return false;
    double const initial = static_cast<double>(product) * static_cast<double>(quality);
    if (!(initial >= 0.0) || initial > static_cast<double>(std::numeric_limits<std::uint32_t>::max()))
        return false;
    std::uint32_t const base = static_cast<std::uint32_t>(initial);
    float const scaled = base * 1.0f * rate;
    // Comparing to float(INT32_MAX) would admit 2^31 after float rounding.
    // The core's zero-to-one-copper minimum is safe and remains native behavior.
    return scaled >= 0.0f && static_cast<double>(scaled) <=
        static_cast<double>(std::numeric_limits<std::int32_t>::max());
}
}

#endif
