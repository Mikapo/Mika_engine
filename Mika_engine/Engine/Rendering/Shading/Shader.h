#pragma once

#include "../Renderer_item.h"
#include "../Texture/Texture_slots.h"
#include <array>
#include <glm/matrix.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace OpenGL
{
    class Shader : public Renderer_item
    {
    public:
        Shader(std::string_view fert_shader_source, std::string_view frag_shader_source);
        ~Shader() override;

        Shader(const Shader&) = delete;
        Shader(Shader&&) = delete;

        Shader& operator=(const Shader&) = delete;
        Shader& operator=(Shader&&) = delete;

        void bind() const noexcept override;
        void unbind() const noexcept override;

        // Set 2D sampler unfiorm
        void set_sampler_uniform(const std::string& name, Texture_slot slot);

        template <typename... Types>
        void set_uniform(const std::string& name, Types... values)
        {
            const int32_t pos = get_uniform_location(name);

            if (pos != -1)
            {
                bind();
                call_gl_uniform(pos, std::forward<Types>(values)...);
            }
        }

    protected:
        uint32_t construct_item() override;

    private:
        struct shader_source
        {
            std::string vertex_source;
            std::string fragment_source;
        };

        static void call_gl_uniform(int32_t pos, float value1, float value2, float value3, float value4) noexcept;
        static void call_gl_uniform(
            int32_t pos, int32_t count, const std::vector<std::array<float, 4>>& arrau) noexcept;
        static void call_gl_uniform(int32_t pos, float value1, float value2, float value3) noexcept;
        static void call_gl_uniform(
            int32_t pos, int32_t count, const std::vector<std::array<float, 3>>& array) noexcept;
        static void call_gl_uniform(int32_t pos, float value1, float value2) noexcept;
        static void call_gl_uniform(int32_t pos, float value) noexcept;
        static void call_gl_uniform(int32_t pos, int32_t value) noexcept;
        static void call_gl_uniform(int32_t pos, const glm::mat4& matrix) noexcept;

        [[nodiscard]] static uint32_t create_shader(std::string_view vertex_shader, std::string_view fragment_shader);
        [[nodiscard]] static uint32_t compile_shader(uint32_t type, std::string_view source);
        [[nodiscard]] int32_t get_uniform_location(const std::string& name);

        std::unordered_map<std::string, int32_t> m_uniform_location_cache;
        std::string m_vert_shader_source;
        std::string m_frag_shader_source;
    };
} // namespace OpenGL
