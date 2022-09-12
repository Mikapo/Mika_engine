
#include "Shaders.h"
#include "Default_shaders/2d_shader.h"
#include "glm/ext/matrix_clip_space.hpp"
#include <fstream>
#include <sstream>

std::unique_ptr<OpenGL::Shader> OpenGL::Shaders::compile_default_shader(bool initialize)
{
    return compile_shader(Default_shader_2d::Source::VERT, Default_shader_2d::Source::FRAG, initialize);
}

std::unique_ptr<OpenGL::Shader> OpenGL::Shaders::compile_shader_from_file(
    std::string_view vert_path, std::string_view frag_path, bool initialize)
{
    const std::string vert_source = parse_shader(vert_path);
    const std::string frag_source = parse_shader(frag_path);

    return compile_shader(vert_source, frag_source, initialize);
}

std::unique_ptr<OpenGL::Shader> OpenGL::Shaders::compile_shader(
    std::string_view vert_shader, std::string_view frag_shader, bool initialize)
{
    std::unique_ptr shader = std::make_unique<Shader>(vert_shader, frag_shader);

    if (initialize)
        shader->initialize();

    return shader;
}

std::string OpenGL::Shaders::parse_shader(std::string_view file_path)
{
    std::ifstream file_stream(file_path.data());
    std::stringstream output_stream;
    std::string line;

    while (getline(file_stream, line))
        output_stream << line << '\n';

    return output_stream.str();
}
