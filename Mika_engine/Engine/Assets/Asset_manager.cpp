#include "Asset_manager.h"

#include "Rendering/Model_loader.h"

std::shared_ptr<Mesh> Asset_manager::get_mesh(const std::string& path) 
{ 
	if (!m_meshes.contains(path))
        m_meshes[path] = std::make_shared<Mesh>(Model_loader::load(path, 0));
        
    return m_meshes[path];
}

std::shared_ptr<Texture> Asset_manager::get_texture(const std::string& path) 
{ 
    if (!m_textures.contains(path))
        m_textures[path] = std::make_shared<Texture>(path);

    return m_textures[path];
}

void Asset_manager::cleanup() 
{
    m_meshes.clear(); 
    m_textures.clear();
}
