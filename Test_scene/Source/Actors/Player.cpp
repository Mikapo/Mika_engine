#include "Player.h"
#include "Objects/Components/Scene_components/Camera_component.h"
#include "Objects/Components/Input_component.h"
#include "Utility/Delegate.h"
#include "Core/Mika_engine.h"

void Player::initialize()
{
	Actor::initialize();

	auto* camera = create_component_cast<Camera_component>(Camera_component::static_class());
	set_active_camera(camera);
	setup_input();

	set_location({ -5.0f, 0.0f, 1.0f });
}

void Player::setup_input()
{
    auto* input = create_component_cast<Input_component>(Input_component::static_class());

	auto* forward_mapping = input->add_axis_mapping<Player>("move_forward", this, &Player::move_forward);
	forward_mapping->add_key(GLFW_KEY_W, 1.0f);
	forward_mapping->add_key(GLFW_KEY_S, -1.0f);

	auto* right_mapping = input->add_axis_mapping<Player>("move_right", this, &Player::move_right);
	right_mapping->add_key(GLFW_KEY_A, -1.0f);
	right_mapping->add_key(GLFW_KEY_D, 1.0f);

	auto* rotate_mapping = input->add_axis_mapping<Player>("rotate", this, &Player::rotate);
	rotate_mapping->add_key(GLFW_KEY_Q, -1.0f);
	rotate_mapping->add_key(GLFW_KEY_E, 1.0f);
}

void Player::move_forward(float input)
{
	if (input == 0)
		return;

	glm::vec3 offset = glm::vec3(1.0f, 0.0f, 0.0f) * input * get_engine()->get_deltatime() * movement_speed;
	add_local_offset(offset);
}

void Player::move_right(float input)
{
	if (input == 0)
		return;

	glm::vec3 offset = glm::vec3(0.0f, 1.0f, 0.0f) * input * get_engine()->get_deltatime() * movement_speed;
	add_local_offset(offset);
}

void Player::rotate(float input)
{
	if (input == 0)
		return;

	Rotator offset = { 0.0f, 25.0f, 0.0f };
	offset = offset * input * get_engine()->get_deltatime();
	add_rotation_offset(offset);
}


