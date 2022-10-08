#include "Settings_ui.h"
#include "../Actors/Light.h"
#include "../Actors/Player.h"
#include "Core/Engine.h"
#include "Objects/Components/Scene_components/Camera_component.h"
#include "Objects/UI/Items/Checkbox.h"
#include "Objects/UI/Items/Color_picker.h"
#include "Objects/UI/Items/Parents/Collapsing_header.h"
#include "Objects/UI/Items/Sliders/Float_slider.h"
#include "Objects/World.h"

void Settings_ui::initialize()
{
    auto window = create_window("Settings");
    setup_camera_settings(window);
    setup_light_settings(window);
    setup_render_settings(window);

    m_on_added_to_viewport.add_object(this, &Settings_ui::on_added_to_viewport);
}

void Settings_ui::on_added_to_viewport(MEngine::World* world)
{
    m_light = world->find_actor_of_class<Light>();
    m_light_original_position = m_light->get_transform().m_location;

    auto player = world->find_actor_of_class<Player>();
    m_player_camera = player->find_component_by_class<MEngine::Camera_component>();
}

void Settings_ui::setup_camera_settings(MEngine::UI_window* window)
{
    auto* camera_settings = window->create_children_cast<MEngine::Collapsing_header>(
        MEngine::Collapsing_header::static_class(), "Camera", 0);

    auto camera_max_clip_slide = camera_settings->create_children_cast<MEngine::Float_slider>(
        MEngine::Float_slider::static_class(), "Max clip", 0);
    camera_max_clip_slide->set_min(1.0f);
    camera_max_clip_slide->set_max(30.0f);
    camera_max_clip_slide->m_on_slider_change.add_object(this, &Settings_ui::change_camera_max_clip);

    auto* camera_min_clip_slide = camera_settings->create_children_cast<MEngine::Float_slider>(
        MEngine::Float_slider::static_class(), "Min clip", 1);
    camera_min_clip_slide->set_min(1.0f);
    camera_min_clip_slide->set_max(30.0f);
    camera_min_clip_slide->m_on_slider_change.add_object(this, &Settings_ui::change_camera_min_clip);

    auto* camera_fov_slide =
        camera_settings->create_children_cast<MEngine::Float_slider>(MEngine::Float_slider::static_class(), "Fov", 2);
    camera_fov_slide->set_min(1.0f);
    camera_fov_slide->set_max(100.0f);
    camera_fov_slide->m_on_slider_change.add_object(this, &Settings_ui::change_camera_fov);
}

void Settings_ui::setup_light_settings(MEngine::UI_window* window)
{
    auto* light_settings = window->create_children_cast<MEngine::Collapsing_header>(
        MEngine::Collapsing_header::static_class(), "Light", 1);

    auto* light_angle_slide =
        light_settings->create_children_cast<MEngine::Float_slider>(MEngine::Float_slider::static_class(), "Angle", 1);
    light_angle_slide->m_on_slider_change.add_object(this, &Settings_ui::change_light_angle);

    auto* light_color_picker =
        light_settings->create_children_cast<MEngine::Color_picker>(MEngine::Color_picker::static_class(), "Color", 0);
    light_color_picker->m_on_color_change.add_object(this, &Settings_ui::change_light_color);
}

void Settings_ui::setup_render_settings(MEngine::UI_window* window)
{
    auto* render_settings = window->create_children_cast<MEngine::Collapsing_header>(
        MEngine::Collapsing_header::static_class(), "Render", 2);

    auto* ambient_enabled_checkbox =
        render_settings->create_children_cast<MEngine::Checkbox>(MEngine::Checkbox::static_class(), "Ambient", 1);
    ambient_enabled_checkbox->m_on_checked_change.add_object(this, &Settings_ui::ambient_enabled);
    ambient_enabled_checkbox->set_checked(true);

    auto* diffuse_enabled_checkbox =
        render_settings->create_children_cast<MEngine::Checkbox>(MEngine::Checkbox::static_class(), "Diffuse", 2);
    diffuse_enabled_checkbox->m_on_checked_change.add_object(this, &Settings_ui::diffuse_enabled);
    diffuse_enabled_checkbox->set_checked(true);

    auto* specular_enabled_checkbox =
        render_settings->create_children_cast<MEngine::Checkbox>(MEngine::Checkbox::static_class(), "Specular", 3);
    specular_enabled_checkbox->m_on_checked_change.add_object(this, &Settings_ui::specular_enabled);
    specular_enabled_checkbox->set_checked(true);

    auto* shadow_enabled_checkbox =
        render_settings->create_children_cast<MEngine::Checkbox>(MEngine::Checkbox::static_class(), "Shadow", 4);
    shadow_enabled_checkbox->m_on_checked_change.add_object(this, &Settings_ui::shadow_enabled);
    shadow_enabled_checkbox->set_checked(true);

    auto* texture_enabled_checkbox =
        render_settings->create_children_cast<MEngine::Checkbox>(MEngine::Checkbox::static_class(), "Texture", 5);
    texture_enabled_checkbox->m_on_checked_change.add_object(this, &Settings_ui::texture_enabled);
    texture_enabled_checkbox->set_checked(true);
}

void Settings_ui::change_camera_max_clip(float max_clip)
{
    if (is_valid(m_player_camera))
        m_player_camera->set_max_clip(max_clip);
}

void Settings_ui::change_camera_min_clip(float min_clip)
{
    if (is_valid(m_player_camera))
        m_player_camera->set_min_clip(min_clip);
}

void Settings_ui::change_camera_fov(float fov)
{
    if (is_valid(m_player_camera))
        m_player_camera->set_fov(fov);
}

void Settings_ui::change_light_angle(float angle)
{
    glm::mat4 rotation = glm::rotate(glm::identity<glm::mat4>(), glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::vec4 new_location = rotation * glm::vec4(m_light_original_position, 1);

    if (is_valid(m_light))
        m_light->set_location(glm::vec3(new_location));
}

void Settings_ui::change_light_color(glm::vec4 color)
{
    if (is_valid(m_light))
        m_light->change_light_color(color);
}

void Settings_ui::ambient_enabled(bool checked)
{
    MEngine::Render_settings settings = get_engine()->get_render_settings();
    settings.ambient_enabled = checked;
    get_engine()->set_render_settings(settings);
}

void Settings_ui::diffuse_enabled(bool checked)
{
    MEngine::Render_settings settings = get_engine()->get_render_settings();
    settings.diffuse_enabled = checked;
    get_engine()->set_render_settings(settings);
}

void Settings_ui::specular_enabled(bool checked)
{
    MEngine::Render_settings settings = get_engine()->get_render_settings();
    settings.specular_enabled = checked;
    get_engine()->set_render_settings(settings);
}

void Settings_ui::shadow_enabled(bool checked)
{
    MEngine::Render_settings settings = get_engine()->get_render_settings();
    settings.shadow_enabled = checked;
    get_engine()->set_render_settings(settings);
}

void Settings_ui::texture_enabled(bool checked)
{
    MEngine::Render_settings settings = get_engine()->get_render_settings();
    settings.texture_enabled = checked;
    get_engine()->set_render_settings(settings);
}
