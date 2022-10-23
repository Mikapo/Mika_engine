#include "Transform.h"

namespace MEngine
{
    Rotator Rotator::operator-(const Rotator& other) const noexcept
    {
        return Rotator(m_pitch - other.m_pitch, m_yaw - other.m_yaw, m_roll - other.m_roll);
    }

    Rotator Rotator::operator+(const Rotator& other) const noexcept
    {
        return Rotator(m_pitch + other.m_pitch, m_yaw + other.m_yaw, m_roll + other.m_roll);
    }

    Rotator Rotator::operator*(float value) const noexcept
    {
        return Rotator(m_pitch * value, m_yaw * value, m_roll * value);
    }

    float Rotator::difference(const Rotator& other) const
    {
        const float pitch_difference = glm::abs(m_pitch - other.m_pitch);
        const float yaw_difference = glm::abs(m_yaw - other.m_yaw);
        const float roll_difference = glm::abs(m_roll - other.m_roll);

        return pitch_difference + yaw_difference + roll_difference;
    }

    glm::mat4 Rotator::calculate_rotation_matrix() const
    {
        const Directional_vectors default_directions;
        const glm::mat4 roll = glm::rotate(glm::mat4(1), glm::radians(m_roll), default_directions.m_forward);
        const glm::mat4 pitch = glm::rotate(glm::mat4(1), glm::radians(m_pitch), default_directions.m_right);
        const glm::mat4 yaw = glm::rotate(glm::mat4(1), glm::radians(m_yaw), default_directions.m_up);
        return yaw * pitch * roll;
    }

    Directional_vectors Rotator::calculate_directional_vectors() const
    {
        const glm::mat4 rotation_matrix = calculate_rotation_matrix();
        const glm::vec3 forward = {rotation_matrix[0][0], rotation_matrix[0][1], rotation_matrix[0][2]};
        const glm::vec3 right = {rotation_matrix[1][0], rotation_matrix[1][1], rotation_matrix[1][2]};
        const glm::vec3 up = {rotation_matrix[2][0], rotation_matrix[2][1], rotation_matrix[2][2]};
        return {forward, right, up};
    }

    glm::mat4 Transform::calculate_model() const
    {
        const glm::mat4 rotation = m_rotation.calculate_rotation_matrix();
        const glm::mat4 scale = calculate_scale_matrix();
        const glm::mat4 translation = calculate_translate_matrix();
        return translation * rotation * scale;
    }

    glm::mat4 Transform::calculate_translate_matrix() const
    {
        return glm::translate(glm::mat4(1), m_location);
    }

    glm::mat4 Transform::calculate_scale_matrix() const
    {
        return glm::scale(glm::mat4(1), m_scale);
    }

    glm::mat4 Transform::calculate_rotation_matrix() const
    {
        return m_rotation.calculate_rotation_matrix();
    }

} // namespace MEngine
