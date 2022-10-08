#include "Mesh_component.h"
#include "Objects/Actor.h"
#include "Objects/World.h"

namespace Mika_engine
{
    Mesh_component::Mesh_component() noexcept : m_mesh("")
    {
    }

    void Mesh_component::initialize()
    {
        Scene_component::initialize();

        get_world()->register_mesh_component(this);
    }

    void Mesh_component::set_mesh(std::string_view mesh_path) noexcept
    {
        m_mesh = Mesh(mesh_path);
    }

    void Mesh_component::set_material(const Material& material) noexcept
    {
        m_material = material;
    }

    Material Mesh_component::get_material() const noexcept
    {
        return m_material;
    }

    std::optional<Mesh_data> Mesh_component::get_mesh_data() const noexcept
    {
        Mesh_data mesh_data = {get_world_transform(), m_mesh, m_material};
        return mesh_data;
    }
} // namespace Mika_engine
