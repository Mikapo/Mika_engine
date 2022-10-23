#include "Player.h"

#include "Bullet.h"
#include "Core/Engine.h"
#include "Objects/Components/Input_component.h"
#include "Objects/Components/Scene_components/Camera_component.h"
#include "Objects/Components/Scene_components/collision_component.h"
#include "Objects/World.h"
#include "Utility/Delegate.h"

void Player::initialize()
{
    Actor::initialize();

    auto* camera = create_component_cast<MEngine::Camera_component>(MEngine::Camera_component::static_class());
    set_active_camera(camera);
    setup_input();

    auto* collision = create_component_cast<MEngine::Collision_component>(MEngine::Collision_component::static_class());
    collision->set_relative_scale({0.1F, 0.1F, 0.1F});
}

void Player::setup_input()
{
    auto* input = create_component_cast<MEngine::Input_component>(MEngine::Input_component::static_class());

    auto* forward_mapping = input->add_axis_mapping<Player>("move_forward", this, &Player::move_forward);
    forward_mapping->add_key(MEngine::Input_key::W, 1.0F);
    forward_mapping->add_key(MEngine::Input_key::S, -1.0F);

    auto* right_mapping = input->add_axis_mapping<Player>("move_right", this, &Player::move_right);
    right_mapping->add_key(MEngine::Input_key::A, -1.0F);
    right_mapping->add_key(MEngine::Input_key::D, 1.0F);

    auto* rotate_mapping = input->add_axis_mapping<Player>("rotate", this, &Player::rotate);
    rotate_mapping->add_key(MEngine::Input_key::Q, -1.0F);
    rotate_mapping->add_key(MEngine::Input_key::E, 1.0F);

    input->add_action_mapping("shoot", MEngine::Input_key::F, MEngine::Input_action::press, this, &Player::shoot);
}

void Player::move_forward(float input)
{
    if (input == 0)
        return;

    glm::vec3 offset = glm::vec3(1.0F, 0.0F, 0.0F) * input * get_engine()->get_deltatime() * m_movement_speed;
    add_local_offset(offset, true);
}

void Player::move_right(float input)
{
    if (input == 0)
        return;

    glm::vec3 offset = glm::vec3(0.0F, 1.0F, 0.0F) * input * get_engine()->get_deltatime() * m_movement_speed;
    add_local_offset(offset, true);
}

void Player::rotate(float input)
{
    if (input == 0)
        return;

    MEngine::Rotator offset = {0.0F, 25.0F, 0.0F};
    offset = offset * input * get_engine()->get_deltatime();
    add_rotation_offset(offset, true);
}

void Player::shoot()
{
    auto* bullet = get_world()->spawn_actor_cast<Bullet>(Bullet::static_class());
    bullet->set_rotation(get_rotation());

    const glm::vec3 bullet_location = get_location() + get_forward_vector();
    bullet->set_location(bullet_location);
    bullet->m_velocity = get_forward_vector();
}
