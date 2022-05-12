#pragma once

#define GLM_FORCE_RADIANS

#include <glm/vec3.hpp>
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include <iostream>

struct Coordinate_system
{
	Coordinate_system() = default;
	Coordinate_system(glm::vec3 forward, glm::vec3 right , glm::vec3 up)
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

	Rotator operator- (const Rotator& other) const
	{ 
		return Rotator(m_pitch - other.m_pitch, m_yaw - other.m_yaw, m_roll - other.m_roll);
	}
	Rotator operator+ (const Rotator& other) const
	{
		return Rotator(m_pitch + other.m_pitch, m_yaw + other.m_yaw, m_roll + other.m_roll);
	}
	Rotator operator* (float value) const
	{
		return Rotator(m_pitch * value, m_yaw * value, m_roll * value);
	}

	float difference(const Rotator& other) const
	{
		float pitch_difference = m_pitch - other.m_pitch;
		if (pitch_difference < 0)
			pitch_difference *= -1;

		float yaw_difference = m_yaw - other.m_yaw;
		if (yaw_difference < 0)
			yaw_difference *= -1;

		float roll_difference = m_roll - other.m_roll;
		if (roll_difference < 0)
			roll_difference *= -1;

		return pitch_difference + yaw_difference + roll_difference;
	}

	glm::mat4 calculate_rotation_matrix(Coordinate_system coord_system = Coordinate_system()) const
	{
		const glm::mat4 identity(1);
		const glm::mat4 roll = glm::rotate(identity, glm::radians(m_roll), coord_system.m_forward);
		const glm::mat4 pitch = glm::rotate(identity, glm::radians(m_pitch), coord_system.m_right);
		const glm::mat4 yaw = glm::rotate(identity, glm::radians(m_yaw), coord_system.m_up);
		return yaw * pitch * roll;
	}

	Coordinate_system calculate_coordinate_system_from_rotation() const
	{
		const glm::mat4 rotation_matrix = calculate_rotation_matrix();
		const glm::vec3 forward = { rotation_matrix[0][0], rotation_matrix[0][1], rotation_matrix[0][2] };
		const glm::vec3 right = { rotation_matrix[1][0], rotation_matrix[1][1], rotation_matrix[1][2] };
		const glm::vec3 up = { rotation_matrix[2][0], rotation_matrix[2][1], rotation_matrix[2][2] };
		return { forward, right, up };
	}

};

struct Transform
{
	Transform() = default;
	Transform(glm::vec3 location, Rotator rotation, glm::vec3 scale)
		: m_location(location), m_rotation(rotation), m_scale(scale) {}

	glm::vec3 m_location = {0.0f, 0.0f, 0.0f};
	Rotator m_rotation = {0.0f, 0.0f, 0.0f};
	glm::vec3 m_scale = {1.0f, 1.0f, 1.0f};

	glm::mat4 calculate_model(Coordinate_system coord_system = Coordinate_system()) const
	{
		const glm::mat4 identity(1);
		const glm::mat4 rotation = m_rotation.calculate_rotation_matrix(coord_system);
		const glm::mat4 scale = glm::scale(identity, m_scale);
		const glm::mat4 translation = glm::translate(identity, m_location);
		return  translation * rotation * scale;
	}
};