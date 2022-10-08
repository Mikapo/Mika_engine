#pragma once

#include <cstdint>

namespace MEngine
{
    enum class Axis_comparison_result : uint8_t
    {
        left,
        right,
        overlap
    };
} // namespace MEngine
