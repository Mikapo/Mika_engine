#pragma once

#include "Rendering/OpenGL/Application/Key.h"

namespace MEngine
{
    using Input_key = OpenGL::Input_key;
    using Input_action = OpenGL::Input_action;

    struct Input
    {
        Input_key key = Input_key::unkown;
        Input_action action = Input_action::unkown;
    };
} // namespace MEngine
