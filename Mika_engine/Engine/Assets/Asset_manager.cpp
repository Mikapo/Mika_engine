#include "Asset_manager.h"

#include "Rendering/Model_loader.h"
#include "Rendering/Texture/Textures.h"

std::shared_ptr<Mesh> Asset_manager::get_mesh(const std::string& path)
{
    auto found_mesh = m_meshes.find(path);

    if (found_mesh == m_meshes.end())
    {
        std::unique_ptr<OpenGL::Buffers> mesh_buffers = OpenGL::Model_loader::load(path, 0);
        std::shared_ptr<Mesh> new_mesh = std::make_shared<Mesh>(std::move(mesh_buffers));
        m_meshes.emplace(path, new_mesh);
        return new_mesh;
    }

    return found_mesh->second;
}

std::shared_ptr<OpenGL::Texture> Asset_manager::get_texture(const std::string& path, OpenGL::Texture_slot slot)
{
    auto found_texture = m_textures.find(path);

    if (found_texture == m_textures.end())
    {
        std::shared_ptr<OpenGL::Texture> new_texture = OpenGL::Textures::load_texture_from_file(path, slot, false);
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
