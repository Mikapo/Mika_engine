#pragma once

#include "../Buffers/Buffers.h"
#include "../Buffers/Frame_buffer.h"
#include "../Texture/Depth_map.h"
#include "Shader.h"
#include <glm/mat4x4.hpp>
#include <memory>

namespace OpenGL
{
    class Shadow_map
    {
    public:
        Shadow_map();
        ~Shadow_map() = default;

        Shadow_map(const Shadow_map&) = delete;
        Shadow_map(Shadow_map&&) = delete;

        Shadow_map& operator=(const Shadow_map&) = delete;
        Shadow_map& operator=(Shadow_map&&) = delete;

        void init(std::unique_ptr<Shader> shadow_map_shader);
        void bind_frame_buffer() const noexcept;
        void unbind_frame_buffer() const noexcept;
        void bind_depth_map() const noexcept;
        void unbind_depth_map() const noexcept;
        [[nodiscard]] Shader* get_shader() const noexcept;
        void get_shadow_resolution(int32_t& out_width, int32_t& out_height) const noexcept;

    private:
        bool m_has_been_initialized = false;
        std::unique_ptr<Shader> m_shader = nullptr;
        Frame_buffer m_frame_buffer;
        Depth_map m_depth_map;
    };
} // namespace OpenGL
