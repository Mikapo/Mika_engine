#pragma once

#include "Scene_component.h"

#include "Datatypes/Frame_data.h"

namespace MEngine
{
    class Camera_component : public Scene_component
    {
        GENERATED_BODY(Camera_component)

    public:
        void set_min_clip(float min_clip) noexcept;
        void set_max_clip(float max_clip) noexcept;
        void set_fov(float fov) noexcept;

        [[nodiscard]] float get_min_clip() const noexcept;
        [[nodiscard]] float get_max_clip() const noexcept;
        [[nodiscard]] float get_fov() const noexcept;

        [[nodiscard]] Camera_data get_camera_data() const noexcept;

    private:
        float m_min_clip = 0.1f;
        float m_max_clip = 100.0f;
        float m_fov = 50.0f;
    };
} // namespace MEngine
