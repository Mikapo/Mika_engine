#pragma once

#include "Objects/Components/Scene_components/Camera_component.h"
#include "Objects/UI/UI.h"

namespace MEngine
{
    class Camera_component;
} // namespace MEngine

class Light;
class Settings_ui : public MEngine::UI
{
    GENERATED_BODY(Settings_ui)

public:
    void initialize() override;

private:
    void on_added_to_viewport(MEngine::World* world);
    void setup_camera_settings(MEngine::UI_window* window);
    void setup_light_settings(MEngine::UI_window* window);
    void setup_render_settings(MEngine::UI_window* window);
    void change_camera_max_clip(float max_clip);
    void change_camera_min_clip(float min_clip);
    void change_camera_fov(float fov);
    void change_light_angle(float angle);
    void change_light_color(glm::vec4 color);
    void ambient_enabled(bool checked);
    void diffuse_enabled(bool checked);
    void specular_enabled(bool checked);
    void shadow_enabled(bool checked);
    void texture_enabled(bool checked);

    Light* m_light = nullptr;
    MEngine::Camera_component* m_player_camera = nullptr;
    glm::vec3 m_light_original_position;
};
