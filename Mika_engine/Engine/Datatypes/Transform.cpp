#include "Transform.h"

Rotator Rotator::operator-(const Rotator& other) const 
{
	return Rotator(m_pitch - other.m_pitch, m_yaw - other.m_yaw, m_roll - other.m_roll);
}

Rotator Rotator::operator+(const Rotator& other) const
{
	return Rotator(m_pitch + other.m_pitch, m_yaw + other.m_yaw, m_roll + other.m_roll);
}

Rotator Rotator::operator*(float value) const
{ 
	return Rotator(m_pitch * value, m_yaw * value, m_roll * value);
}

float Rotator::difference(const Rotator& other) const 
{
    float pitch_difference = glm::abs(m_pitch - other.m_pitch);
    float yaw_difference = glm::abs(m_yaw - other.m_yaw);
    float roll_difference = glm::abs(m_roll - other.m_roll);

    return pitch_difference + yaw_difference + roll_difference;
}

glm::mat4 Rotator::calculate_rotation_matrix(Directional_vectors coord_system) const
{
    const glm::mat4 identity(1);
    const glm::mat4 roll = glm::rotate(identity, glm::radians(m_roll), coord_system.m_forward);
    const glm::mat4 pitch = glm::rotate(identity, glm::radians(m_pitch), coord_system.m_right);
    const glm::mat4 yaw = glm::rotate(identity, glm::radians(m_yaw), coord_system.m_up);
    return yaw * pitch * roll;
}

Directional_vectors Rotator::calculate_directional_vectors_from_rotation() const
{
    const glm::mat4 rotation_matrix = calculate_rotation_matrix();
    const glm::vec3 forward = {rotation_matrix[0][0], rotation_matrix[0][1], rotation_matrix[0][2]};
    const glm::vec3 right = {rotation_matrix[1][0], rotation_matrix[1][1], rotation_matrix[1][2]};
    const glm::vec3 up = {rotation_matrix[2][0], rotation_matrix[2][1], rotation_matrix[2][2]};
    return {forward, right, up};
}

glm::mat4 Transform::calculate_model(Directional_vectors coord_system) const
{
    const glm::mat4 identity(1);
    const glm::mat4 rotation = m_rotation.calculate_rotation_matrix(coord_system);
    const glm::mat4 scale = glm::scale(identity, m_scale);
    const glm::mat4 translation = glm::translate(identity, m_location);
    return translation * rotation * scale;
}
