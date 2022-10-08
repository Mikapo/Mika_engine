#include "Camera_component.h"

#include "Objects/Actor.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace MEngine
{
    float Camera_component::get_min_clip() const noexcept
    {
        return m_min_clip;
    }

    float Camera_component::get_max_clip() const noexcept
    {
        return m_max_clip;
    }

    float Camera_component::get_fov() const noexcept
    {
        return m_fov;
    }

    void Camera_component::set_min_clip(float min_clip) noexcept
    {
        m_min_clip = min_clip;
    }

    void Camera_component::set_max_clip(float max_clip) noexcept
    {
        m_max_clip = max_clip;
    }

    void Camera_component::set_fov(float fov) noexcept
    {
        m_fov = fov;
    }

    Camera_data Camera_component::get_camera_data() const noexcept
    {
        return {get_world_transform(), m_min_clip, m_max_clip, m_fov};
    }

} // namespace MEngine
