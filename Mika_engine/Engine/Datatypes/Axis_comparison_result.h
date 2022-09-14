#pragma once

#include <cstdint>

namespace Mika_engine
{
    enum class Axis_comparison_result : uint8_t
    {
        left,
        right,
        overlap
    };
} // namespace Mika_engine
