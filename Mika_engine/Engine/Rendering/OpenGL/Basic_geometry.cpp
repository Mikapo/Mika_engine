#include "Basic_geometry.h"

std::unique_ptr<OpenGL::Buffers> OpenGL::Basic_geometry::create_square_buffers(bool initialize)
{
    Vertex_buffer_layout layout = create_2d_layout();

    constexpr float radius = 0.5F;

    std::vector<float> square_vertices = {-radius, -radius, 0.0F, 0.0F, radius,  -radius, 1.0F, 0.0F,
                                          radius,  radius,  1.0F, 1.0F, -radius, radius,  0.0F, 1.0F};

    std::vector<uint32_t> square_indices = {0, 1, 2, 2, 3, 0};

    return create_buffers(std::move(square_vertices), std::move(square_indices), std::move(layout), initialize);
}

std::unique_ptr<OpenGL::Buffers> OpenGL::Basic_geometry::create_triangle_buffers(bool initialize)
{
    Vertex_buffer_layout layout = create_2d_layout();

    constexpr float height = 0.5F;
    std::vector<float> triangle_vertices = {-height, -height, 0.0F, 0.0F, height, -height,
                                            0.0F,    0.0F,    0.0F, 0.0F, 0.0F};

    std::vector<uint32_t> triangle_indices = {0, 1, 2};

    return create_buffers(std::move(triangle_vertices), std::move(triangle_indices), std::move(layout), initialize);
}

OpenGL::Vertex_buffer_layout OpenGL::Basic_geometry::create_2d_layout()
{
    Vertex_buffer_layout layout;

    // vertex position
    layout.push_float(2);

    // texture coordinates
    layout.push_float(2);

    return layout;
}

std::unique_ptr<OpenGL::Buffers> OpenGL::Basic_geometry::create_buffers(
    std::vector<float> vertices, std::vector<uint32_t> indices, Vertex_buffer_layout layout, bool initialize = true)
{
    std::unique_ptr buffers = std::make_unique<Buffers>(std::move(vertices), std::move(indices), std::move(layout));

    if (initialize)
        buffers->initialize();

    return buffers;
}
