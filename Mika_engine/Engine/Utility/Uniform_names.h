#pragma once

#define UNIFORM_TYPE constexpr const char*

namespace Uniform_names
{
    UNIFORM_TYPE model = "u_model";
    UNIFORM_TYPE view = "u_view";
    UNIFORM_TYPE projection = "u_projection";
    UNIFORM_TYPE light_space = "u_light_space_matrix";
    UNIFORM_TYPE near_plane = "u_near_plane";
    UNIFORM_TYPE far_plane = "u_far_plane";
    UNIFORM_TYPE eye_location = "u_eye_loc";
    UNIFORM_TYPE light_color = "u_light_color";
    UNIFORM_TYPE light_location = "u_light_loc";
    UNIFORM_TYPE ambient = "u_ambient";
    UNIFORM_TYPE ambient_enabled = "u_ambient_enabled";
    UNIFORM_TYPE diffuse = "u_diffuse";
    UNIFORM_TYPE diffuse_enabled = "u_diffuse_enabled";
    UNIFORM_TYPE specular = "u_specular";
    UNIFORM_TYPE specular_enabled = "u_specular_enabled";
    UNIFORM_TYPE shininess = "u_shininess";
    UNIFORM_TYPE default_color = "u_default_color";
    UNIFORM_TYPE has_texture = "u_has_texture";
    UNIFORM_TYPE texture = "u_texture";
    UNIFORM_TYPE texture_enabled = "u_texture_enabled";
    UNIFORM_TYPE shadow_map = "u_shadow_map";
    UNIFORM_TYPE shadow_enabled = "u_shadow_enabled";
}

#undef UNIFORM_TYPE