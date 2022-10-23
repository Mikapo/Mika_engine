#pragma once

#include <string_view>

namespace MEngine
{
    class Mesh
    {
    public:
        /**
         * @param File path where the mesh is located
         */
        Mesh(std::string_view mesh_location) noexcept;

        Mesh(const Mesh&) = default;
        Mesh(Mesh&&) = default;

        Mesh& operator=(const Mesh&) = default;
        Mesh& operator=(Mesh&&) = default;

        /**
         * @return file path where the mesh is located
         */
        [[nodiscard]] std::string_view get_mesh_location() const noexcept;

    private:
        std::string m_mesh_location;
    };
} // namespace MEngine
