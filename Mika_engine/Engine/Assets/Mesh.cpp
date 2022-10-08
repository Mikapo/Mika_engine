#include "Mesh.h"

namespace Mika_engine
{
    Mesh::Mesh(std::string_view mesh_location) noexcept : m_mesh_location(mesh_location)
    {
    }

    std::string_view Mesh::get_mesh_location() const noexcept
    {
        return m_mesh_location;
    }
} // namespace Mika_engine
