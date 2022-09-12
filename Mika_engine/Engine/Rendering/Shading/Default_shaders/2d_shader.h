#pragma once

namespace OpenGL::Default_shader_2d::Source
{
    constexpr const char* FRAG = R"(
        
    #version 330 core

    layout(location = 0) out vec4 out_frag_color;

    in OUT 
    {
        vec2 tex_coordinates;
    } shader_in;

    uniform vec4 u_color = vec4(0.9f, 0.9f, 0.9f, 1.0f);

    uniform int u_uses_texture = 0;
    uniform sampler2D u_texture;

    void main() 
    {    
	    if (u_uses_texture == 1)
		    out_frag_color = texture(u_texture, shader_in.tex_coordinates);
	    else
		    out_frag_color = u_color;
    })";

    constexpr const char* VERT = R"(

    #version 330 core

    layout (location = 0) in vec2 l_position;
    layout (location = 1) in vec2 l_tex_coordinates;

    out OUT 
    {
        vec2 tex_coordinates;
    } shader_out;

    uniform mat4 u_projection = mat4(1);
    uniform mat4 u_model = mat4(1);

    void main() 
    {
        gl_Position = u_projection *  u_model * vec4(l_position, 0, 1);
        shader_out.tex_coordinates = l_tex_coordinates;
    })";

} // namespace OpenGL::Default_shader_2d::Source

namespace OpenGL::Default_shader_2d::Uniforms
{
    constexpr const char* PROJECTION = "u_projection";
    constexpr const char* MODEL = "u_model";
    constexpr const char* COLOR = "u_color";
    constexpr const char* USES_TEXTURE = "u_uses_texture";
    constexpr const char* TEXTURE = "u_texture";
} // namespace OpenGL::Default_shader_2d::Uniforms
