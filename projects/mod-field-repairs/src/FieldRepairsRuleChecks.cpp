#include "FieldRepairsRules.h"

namespace
{
using FieldRepairs::NativeCostSafe;
constexpr auto U32Max = std::numeric_limits<std::uint32_t>::max();
constexpr auto Infinity = std::numeric_limits<float>::infinity();
constexpr auto NotANumber = std::numeric_limits<float>::quiet_NaN();

static_assert(FieldRepairs::ConsentValid(30000, 29999));
static_assert(!FieldRepairs::ConsentValid(30000, 30000));
static_assert(!FieldRepairs::ConsentValid(30000, 30001));
static_assert(FieldRepairs::ConsentSeconds(30000, 29999) == 1);
static_assert(FieldRepairs::ConsentSeconds(30000, 30000) == 0);
static_assert(FieldRepairs::ConsentSeconds(30000, 0) == 30);

static_assert(NativeCostSafe(100, 90, 3, 1.0f, 1.0f));
static_assert(NativeCostSafe(3, 0, 1, 0.5f, 1.5f));
static_assert(NativeCostSafe(100, 100, 3, 1.0f, 1.0f));
static_assert(!NativeCostSafe(100, 101, 3, 1.0f, 1.0f));
static_assert(NativeCostSafe(100, 0, 1, 0.0f, 1.0f));
static_assert(NativeCostSafe(100, 0, 1, 1.0f, 0.0f));

// The native uint32 product must be safe even if a later zero factor would
// otherwise make the price small. Equality at UINT32_MAX is still representable.
static_assert(!NativeCostSafe(U32Max, 0, 2, 0.0f, 1.0f));
static_assert(NativeCostSafe(U32Max, 0, 1, 0.0f, 1.0f));
static_assert(!NativeCostSafe(U32Max, 0, 1, 2.0f, 1.0f));
static_assert(!NativeCostSafe(2147483647u, 0, 1, 1.0f, 1.0f));
static_assert(NativeCostSafe(2147483520u, 0, 1, 1.0f, 1.0f));
static_assert(!NativeCostSafe(1073741824u, 0, 1, 1.0f, 2.0f));

static_assert(!NativeCostSafe(1, 0, 1, -1.0f, 1.0f));
static_assert(!NativeCostSafe(1, 0, 1, Infinity, 1.0f));
static_assert(!NativeCostSafe(1, 0, 1, NotANumber, 1.0f));
static_assert(!NativeCostSafe(1, 0, 1, 1.0f, -1.0f));
static_assert(!NativeCostSafe(1, 0, 1, 1.0f, Infinity));
static_assert(!NativeCostSafe(1, 0, 1, 1.0f, NotANumber));
static_assert(!NativeCostSafe(1, 0, 1, 1.0f, std::numeric_limits<float>::max()));
}
