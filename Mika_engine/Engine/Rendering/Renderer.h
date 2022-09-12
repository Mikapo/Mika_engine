#pragma once

namespace OpenGL
{
    class Buffers;
    class Shader;
    class Shadow_map;

    class Renderer
    {
    public:
        Renderer() = delete;

        static void draw(Buffers& buffers, const Shader& shader) noexcept;
        static void start_drawing_to_shadow_map(const Shadow_map& shadow_map);
        static void stop_drawing_to_shadow_map(
            const Shadow_map& shadow_map, int32_t window_width, int32_t window_height);
    };
} // namespace OpenGL
