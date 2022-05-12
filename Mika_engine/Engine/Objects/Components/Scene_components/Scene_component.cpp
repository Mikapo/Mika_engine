#include "Scene_component.h"

#include <glm/ext/matrix_transform.hpp>
#include "Objects/Actor.h"
#include <glm/gtx/matrix_decompose.hpp>

void Scene_component::initialize()
{
	Actor_component::initialize();

	update_directional_vectors();
	update_world_transform();
	get_owner()->m_on_transform_change.add_object(this, &Scene_component::on_owner_transform_change);
}

void Scene_component::set_relative_transform(Transform transform)
{
	m_relative_transform = transform;
	update_directional_vectors();
	update_world_transform();
}

Transform Scene_component::get_relative_transform() const
{
	return m_relative_transform;
}

Transform Scene_component::get_world_transform() const
{
	return m_world_transform;
}

void Scene_component::set_relative_location(glm::vec3 new_location)
{
	Transform transform = get_relative_transform();
	transform.m_location = new_location;
	set_relative_transform(transform);
}

glm::vec3 Scene_component::get_relative_forward_vector()
{
	return m_local_coordinate_system.m_forward;;
}

glm::vec3 Scene_component::get_relative_up_vector()
{
	return m_local_coordinate_system.m_up;
}

void Scene_component::update_directional_vectors()
{
	m_local_coordinate_system = get_relative_transform().m_rotation.calculate_coordinate_system_from_rotation();
}

void Scene_component::update_world_transform()
{
	const glm::mat4 owner_model = get_owner()->get_transform().calculate_model();
	const glm::mat4 component_relative_model = get_relative_transform().calculate_model();
	const glm::mat4 component_world_model = owner_model * component_relative_model;

	glm::vec3 scale;
	glm::quat rotation_quat;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(component_world_model, scale, rotation_quat, translation, skew, perspective);

	glm::vec3 rotation = glm::degrees(glm::eulerAngles(rotation_quat));

	m_world_transform.m_location = translation;
	m_world_transform.m_rotation = { rotation.y, rotation.z, rotation.x };
	m_world_transform.m_scale = scale;
}

void Scene_component::on_owner_transform_change(Actor* owner)
{
	update_world_transform();
}
