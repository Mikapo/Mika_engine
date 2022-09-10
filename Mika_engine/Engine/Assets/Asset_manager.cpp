#include "Asset_manager.h"

#include "Rendering/Model_loader.h"

std::shared_ptr<Mesh> Asset_manager::get_mesh(const std::string& path)
{
    auto found_mesh = m_meshes.find(path);

    if (found_mesh == m_meshes.end())
    {
        std::unique_ptr<Buffers> mesh_buffers = Model_loader::load(path, 0);
        std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>(std::move(mesh_buffers));
        m_meshes.emplace(path, new_mesh);
        return new_mesh;
    }

    return found_mesh->second;
}

std::shared_ptr<Texture> Asset_manager::get_texture(const std::string& path)
{
    auto found_texture = m_textures.find(path);

    if (found_texture == m_textures.end())
    {
        std::shared_ptr<Texture> new_texture = std::make_shared<Texture>(path);
        m_textures.emplace(path, new_texture);
        return new_texture;
    }

    return found_texture->second;
}

void Asset_manager::cleanup() noexcept
{
    m_meshes.clear();
    m_textures.clear();
}
