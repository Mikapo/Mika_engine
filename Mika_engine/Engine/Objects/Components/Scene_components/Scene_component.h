#pragma once

#include "../Actor_component.h"
#include "Datatypes/Transform.h"

class Scene_component : public Actor_component
{
    GENERATED_BODY(Scene_component)

public:
	void initialize() override;
	void set_relative_transform(Transform transform);
    Transform get_relative_transform() const noexcept;
    void set_relative_location(glm::vec3 new_location);
    void set_relative_rotation(Rotator new_rotation);
    void set_relative_scale(glm::vec3 new_scale);
    Transform get_world_transform() const noexcept;
    glm::vec3 get_relative_forward_vector() const noexcept;
    glm::vec3 get_relative_up_vector() const noexcept;

protected:
    Transform calculate_component_world_transform(Transform owner_transform);
    virtual void update_world_transform();

private:
	void update_directional_vectors();
    void on_owner_transform_change(Actor* owner);

	Transform m_relative_transform;
	Transform m_world_transform;
	Directional_vectors m_local_directional_vectors;
};

