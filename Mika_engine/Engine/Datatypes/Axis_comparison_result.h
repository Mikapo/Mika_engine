#pragma once

#include <cstdint>

namespace MEngine
{
    // Used by collision algorithms
    enum class Axis_comparison_result : uint8_t
    {
        left,
        right,
        overlap
    };
} // namespace MEngine
