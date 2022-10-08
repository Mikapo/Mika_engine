#include "GL/glew.h"

#include "Buffers/Buffers.h"
#include "Renderer.h"
#include "Shading/Shader.h"
#include "Shading/Shadow_map.h"

void OpenGL::Renderer::draw(const Buffers& buffers, const Shader& shader) noexcept
{
    buffers.bind();
    shader.bind();

    const auto indices_count = static_cast<GLsizei>(buffers.get_indices_count());
    glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_INT, nullptr);
}

void OpenGL::Renderer::start_drawing_to_shadow_map(const Shadow_map& shadow_map)
{
    int32_t shadow_width = 0, shadow_height = 0;
    shadow_map.get_shadow_resolution(shadow_width, shadow_height);
    shadow_map.bind_frame_buffer();
    glViewport(0, 0, shadow_width, shadow_height);
    glCullFace(GL_FRONT);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void OpenGL::Renderer::stop_drawing_to_shadow_map(
    const Shadow_map& shadow_map, int32_t window_width, int32_t window_height)
{
    glCullFace(GL_BACK);
    shadow_map.unbind_frame_buffer();
    glViewport(0, 0, static_cast<GLsizei>(window_width), static_cast<GLsizei>(window_height));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
