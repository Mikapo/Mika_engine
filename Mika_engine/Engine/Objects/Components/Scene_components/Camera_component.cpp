#include "Camera_component.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Objects/Actor.h"

float Camera_component::get_min_clip() const
{
    return m_min_clip;
}

float Camera_component::get_max_clip() const
{
    return m_max_clip;
}

float Camera_component::get_fov() const
{
    return m_fov;
}

void Camera_component::set_min_clip(float min_clip)
{
    m_min_clip = min_clip;
}

void Camera_component::set_max_clip(float max_clip)
{
    m_max_clip = max_clip;
}

void Camera_component::set_fov(float fov)
{
    m_fov = fov;
}

Camera_data Camera_component::get_camera_data() const
{
    return { get_world_transform(), m_min_clip, m_max_clip, m_fov };
}
