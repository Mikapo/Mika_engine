#pragma once

#include "Texture_base.h"

namespace OpenGL
{
    class Depth_map : public Texture_base
    {
    public:
        Depth_map(int32_t width, int32_t height) noexcept;
        ~Depth_map() override = default;

        Depth_map(const Depth_map&) = delete;
        Depth_map(Depth_map&&) = delete;

        Depth_map& operator=(const Depth_map&) = delete;
        Depth_map& operator=(Depth_map&&) = delete;

        void add_depth_map_to_framebuffer();
        void get_resolution(int32_t& out_width, int32_t& out_height) const noexcept;

    protected:
        [[nodiscard]] uint32_t construct_item() override;

    private:
        int32_t m_width = 0, m_height = 0;
    };
} // namespace OpenGL
