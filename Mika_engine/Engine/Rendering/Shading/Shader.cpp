#include "GL/glew.h"

#include "Shader.h"
#include <memory>
#include <stdexcept>

OpenGL::Shader::Shader(std::string_view vert_shader_source, std::string_view frag_shader_source)
    : m_vert_shader_source(vert_shader_source), m_frag_shader_source(frag_shader_source)
{
}

OpenGL::Shader::~Shader()
{
    if (has_been_initialized())
        glDeleteProgram(get_id());
}

void OpenGL::Shader::bind() const noexcept
{
    glUseProgram(get_id());
}

void OpenGL::Shader::unbind() const noexcept
{
    glUseProgram(0);
}

void OpenGL::Shader::set_sampler_uniform(const std::string& name, Texture_slot slot)
{
    set_uniform(name, static_cast<int32_t>(slot));
}

uint32_t OpenGL::Shader::construct_item()
{
    const uint32_t shader_id = create_shader(m_vert_shader_source, m_frag_shader_source);
    glUseProgram(shader_id);

    return shader_id;
}

void OpenGL::Shader::call_gl_uniform(int32_t pos, float value1, float value2, float value3, float value4) noexcept
{
    glUniform4f(pos, value1, value2, value3, value4);
}

void OpenGL::Shader::call_gl_uniform(
    int32_t pos, int32_t count, const std::vector<std::array<float, 4>>& array) noexcept
{
    glUniform4fv(pos, static_cast<GLsizei>(count), array.data()->data());
}

void OpenGL::Shader::call_gl_uniform(int32_t pos, float value1, float value2, float value3) noexcept
{
    glUniform3f(pos, value1, value2, value3);
}

void OpenGL::Shader::call_gl_uniform(
    int32_t pos, int32_t count, const std::vector<std::array<float, 3>>& array) noexcept
{
    glUniform3fv(pos, static_cast<GLsizei>(count), array.data()->data());
}

void OpenGL::Shader::call_gl_uniform(int32_t pos, float value1, float value2) noexcept
{
    glUniform2f(pos, value1, value2);
}

void OpenGL::Shader::call_gl_uniform(int32_t pos, float value) noexcept
{
    glUniform1f(pos, value);
}

void OpenGL::Shader::call_gl_uniform(int32_t pos, int32_t value) noexcept
{
    glUniform1i(pos, value);
}

void OpenGL::Shader::call_gl_uniform(int32_t pos, const glm::mat4& matrix) noexcept
{
    glUniformMatrix4fv(pos, 1, GL_FALSE, &matrix[0][0]);
}

int32_t OpenGL::Shader::get_uniform_location(const std::string& name)
{
    const auto found_location = m_uniform_location_cache.find(name);

    if (found_location != m_uniform_location_cache.end())
        return found_location->second;

    int32_t location = glGetUniformLocation(get_id(), name.data());
    m_uniform_location_cache[name] = location;
    return location;
}

uint32_t OpenGL::Shader::compile_shader(uint32_t type, std::string_view source)
{
    const uint32_t Shader_id = glCreateShader(type);
    const char* src = source.data();
    glShaderSource(Shader_id, 1, &src, nullptr);
    glCompileShader(Shader_id);

    int32_t compile_result = 0;
    glGetShaderiv(Shader_id, GL_COMPILE_STATUS, &compile_result);

    // Shadet compilation error handling
    if (compile_result == GL_FALSE)
    {
        int32_t lenght = 0;
        glGetShaderiv(Shader_id, GL_INFO_LOG_LENGTH, &lenght);

        std::unique_ptr message_buffer = std::make_unique<char[]>(lenght);

        glGetShaderInfoLog(Shader_id, lenght, &lenght, message_buffer.get());
        glDeleteShader(Shader_id);

        throw std::invalid_argument(message_buffer.get());
    }

    return Shader_id;
}

uint32_t OpenGL::Shader::create_shader(std::string_view vertex_shader, std::string_view fragment_shader)
{
    const uint32_t vertex_shader_id = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    const uint32_t fragment_shader_id = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
    const uint32_t program = glCreateProgram();

    glAttachShader(program, vertex_shader_id);
    glAttachShader(program, fragment_shader_id);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return program;
}
