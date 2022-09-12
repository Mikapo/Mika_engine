#pragma once

#include <cstdint>

namespace OpenGL
{
    /*
    You can edit this enum to add more different texture slots.
    OpenGL supports 31 different texture slot.
    But note that your system might support less texture slots than that.
    */
    enum class Texture_slot : uint8_t
    {
        color,
        depth_map
    };
} // namespace OpenGL
