#pragma once

#include "Scene_component.h"

#include "Datatypes/Frame_data.h"

namespace Mika_engine
{
    class Camera_component : public Scene_component
    {
        GENERATED_BODY(Camera_component)

    public:
        float get_min_clip() const noexcept;
        float get_max_clip() const noexcept;
        float get_fov() const noexcept;
        void set_min_clip(float min_clip) noexcept;
        void set_max_clip(float max_clip) noexcept;
        void set_fov(float fov) noexcept;
        Camera_data get_camera_data() const noexcept;

    private:
        float m_min_clip = 0.1f;
        float m_max_clip = 100.0f;
        float m_fov = 50.0f;
    };
} // namespace Mika_engine
