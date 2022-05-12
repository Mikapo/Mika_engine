#pragma once

#include "../Actor_component.h"

class Scene_component : public Actor_component
{
public:
	void initialize() override;
	void set_relative_transform(Transform transform);
	Transform get_relative_transform() const;
	Transform get_world_transform() const;
	void set_relative_location(glm::vec3 new_location);
	glm::vec3 get_relative_forward_vector();
	glm::vec3 get_relative_up_vector();

private:
	void update_directional_vectors();
	void update_world_transform();
	void on_owner_transform_change(Actor* owner);

	Transform m_relative_transform;
	Transform m_world_transform;
	Coordinate_system m_local_coordinate_system;
};

