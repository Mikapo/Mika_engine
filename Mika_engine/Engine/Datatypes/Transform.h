#pragma once

#define GLM_FORCE_RADIANS

#include <glm/vec3.hpp>
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

struct Directional_vectors
{
    Directional_vectors() = default;
    Directional_vectors(glm::vec3 forward, glm::vec3 right, glm::vec3 up)
		: m_forward(forward), m_right(right), m_up(up) {}

	glm::vec3 m_forward =  { 1.0f, 0.0f, 0.0f };
	glm::vec3 m_right = { 0.0f, 1.0f, 0.0f };
	glm::vec3 m_up = { 0.0f, 0.0f, 1.0f };
};

struct Rotator
{
	Rotator() = default;
	Rotator(float pitch, float yaw, float roll)
		: m_pitch(pitch), m_yaw(yaw), m_roll(roll) {}

	float m_pitch = 0;
	float m_yaw = 0;
	float m_roll = 0;

	Rotator operator-(const Rotator& other) const;
    Rotator operator+(const Rotator& other) const;
    Rotator operator*(float value) const;

	float difference(const Rotator& other) const;
	glm::mat4 calculate_rotation_matrix(Directional_vectors coord_system = Directional_vectors()) const;
	Directional_vectors calculate_directional_vectors_from_rotation() const;
};

struct Transform
{
	Transform() = default;
	Transform(glm::vec3 location, Rotator rotation, glm::vec3 scale)
		: m_location(location), m_rotation(rotation), m_scale(scale) {}

	glm::vec3 m_location = {0.0f, 0.0f, 0.0f};
	Rotator m_rotation = {0.0f, 0.0f, 0.0f};
	glm::vec3 m_scale = {1.0f, 1.0f, 1.0f};

	glm::mat4 calculate_model(Directional_vectors coord_system = Directional_vectors()) const;
};