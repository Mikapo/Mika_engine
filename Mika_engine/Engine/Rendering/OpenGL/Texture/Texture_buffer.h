#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

namespace OpenGL
{
    class Texture_buffer
    {
    public:
        void load_buffer_from_file(std::string_view path);
        void add_buffer(std::vector<unsigned char> buffer, int32_t tex_width, int32_t tex_height);

        void free_buffer() noexcept;

        [[nodiscard]] const std::vector<unsigned char>& get_buffer() const noexcept;
        [[nodiscard]] bool has_buffer() const noexcept;
        void get_dimensions(int32_t& width, int32_t& height) const noexcept;

    private:
        static size_t get_correct_buffer_size(int32_t tex_width, int32_t tex_height) noexcept;

        int32_t m_width = 0, m_height = 0;
        std::vector<unsigned char> m_buffer;

        static constexpr int32_t DESIRED_CHANNELS = 4;
    };
} // namespace OpenGL
