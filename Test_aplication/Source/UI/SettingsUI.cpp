#include "SettingsUI.h"
#include "Objects/UI/Items/Checkbox.h"
#include "Objects/UI/Items/Parents/Collapsing_header.h"
#include "Objects/UI/Items/Sliders/Float_slider.h"
#include "Objects/UI/Items/Color_picker.h"
#include "Objects/World.h"
#include "Objects/Components/Scene_components/Camera_component.h"
#include "../Actors/Player.h"
#include "../Actors/Light.h"
#include <iostream>

void SettingsUI::initialize()
{
	UI_window* window = add_window("Settings");
	setup_camera_settings(window);
	setup_light_settings(window);
	setup_render_settings(window);
}

void SettingsUI::on_added_to_viewport(World* world)
{
	UI::on_added_to_viewport(world);

	m_light = world->find_actor_of_class<Light>();
	m_light_original_position = m_light->get_transform().m_location;

	auto* player = world->find_actor_of_class<Player>();
	m_player_camera = player->find_component_by_class<Camera_component>();
}

void SettingsUI::setup_camera_settings(UI_window* window)
{
	auto* camera_settings = window->create_children<Collapsing_header>("Camera", 0);

	auto* camera_max_clip_slide = camera_settings->create_children<Float_slider>("Max clip", 0);
	camera_max_clip_slide->set_min(1.0f);
	camera_max_clip_slide->set_max(30.0f);
	camera_max_clip_slide->m_on_slider_change.add_object(this, &SettingsUI::change_camera_max_clip);

	auto* camera_min_clip_slide = camera_settings->create_children<Float_slider>("Min clip", 1);
	camera_min_clip_slide->set_min(1.0f);
	camera_min_clip_slide->set_max(30.0f);
	camera_min_clip_slide->m_on_slider_change.add_object(this, &SettingsUI::change_camera_min_clip);

	auto* camera_fov_slide = camera_settings->create_children<Float_slider>("Fov", 2);
	camera_fov_slide->set_min(1.0f);
	camera_fov_slide->set_max(100.0f);
	camera_fov_slide->m_on_slider_change.add_object(this, &SettingsUI::change_camera_fov);
}

void SettingsUI::setup_light_settings(UI_window* window)
{
	auto* light_settings = window->create_children<Collapsing_header>("Light", 1);

	auto* light_angle_slide = light_settings->create_children<Float_slider>("Angle", 1);
	light_angle_slide->m_on_slider_change.add_object(this, &SettingsUI::change_light_angle);

	auto* light_color_picker = light_settings->create_children<Color_picker>("Color", 0);
	light_color_picker->m_on_color_change.add_object(this, &SettingsUI::change_light_color);
}

void SettingsUI::setup_render_settings(UI_window* window)
{
	auto* render_settings = window->create_children<Collapsing_header>("Render", 2);

	auto* ambient_enabled_checkbox = render_settings->create_children<Checkbox>("Ambient", 1);
	ambient_enabled_checkbox->m_on_checked_change.add_object(this, &SettingsUI::ambient_enabled);
	ambient_enabled_checkbox->set_checked(true);

	auto* diffuse_enabled_checkbox = render_settings->create_children<Checkbox>("Diffuse", 2);
	diffuse_enabled_checkbox->m_on_checked_change.add_object(this, &SettingsUI::diffuse_enabled);
	diffuse_enabled_checkbox->set_checked(true);

	auto* specular_enabled_checkbox = render_settings->create_children<Checkbox>("Specular", 3);
	specular_enabled_checkbox->m_on_checked_change.add_object(this, &SettingsUI::specular_enabled);
	specular_enabled_checkbox->set_checked(true);

	auto* shadow_enabled_checkbox = render_settings->create_children<Checkbox>("Shadow", 4);
	shadow_enabled_checkbox->m_on_checked_change.add_object(this, &SettingsUI::shadow_enabled);
	shadow_enabled_checkbox->set_checked(true);

	auto* texture_enabled_checkbox = render_settings->create_children<Checkbox>("Texture", 5);
	texture_enabled_checkbox->m_on_checked_change.add_object(this, &SettingsUI::texture_enabled);
	texture_enabled_checkbox->set_checked(true);
}

void SettingsUI::change_camera_max_clip(float max_clip)
{
	if (is_valid(m_player_camera))
		m_player_camera->set_max_clip(max_clip);
}

void SettingsUI::change_camera_min_clip(float min_clip)
{
	if (is_valid(m_player_camera))
		m_player_camera->set_min_clip(min_clip);
}

void SettingsUI::change_camera_fov(float fov)
{
	if (is_valid(m_player_camera))
		m_player_camera->set_fov(fov);
}

void SettingsUI::change_light_angle(float angle)
{
	glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec4 new_location = rotation * glm::vec4(m_light_original_position, 1);
	
	if (is_valid(m_light))
		m_light->set_location(glm::vec3(new_location));
}

void SettingsUI::change_light_color(glm::vec4 color)
{
	if (is_valid(m_light))
		m_light->change_light_color(color);
}

void SettingsUI::ambient_enabled(bool checked)
{
	Render_settings settings = get_engine()->get_render_settings();
	settings.ambient_enabled = checked;
	get_engine()->set_render_settings(settings);
}

void SettingsUI::diffuse_enabled(bool checked)
{
	Render_settings settings = get_engine()->get_render_settings();
	settings.diffuse_enabled = checked;
	get_engine()->set_render_settings(settings);
}

void SettingsUI::specular_enabled(bool checked)
{
	Render_settings settings = get_engine()->get_render_settings();
	settings.specular_enabled = checked;
	get_engine()->set_render_settings(settings);
}

void SettingsUI::shadow_enabled(bool checked)
{
	Render_settings settings = get_engine()->get_render_settings();
	settings.shadow_enabled = checked;
	get_engine()->set_render_settings(settings);
}

void SettingsUI::texture_enabled(bool checked)
{
	Render_settings settings = get_engine()->get_render_settings();
	settings.texture_enabled = checked;
	get_engine()->set_render_settings(settings);
}
