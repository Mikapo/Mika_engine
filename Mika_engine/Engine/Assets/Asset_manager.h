#pragma once

#include "Mesh.h"
#include "Rendering/Texture/Texture.h"
#include <unordered_map>
#include <string>
#include <string_view>
#include <memory>

class Asset_manager
{
public:
    std::shared_ptr<Mesh> get_mesh(const std::string& path);
    std::shared_ptr<OpenGL::Texture> get_texture(const std::string& path, OpenGL::Texture_slot slot);
    void cleanup() noexcept;

private:
    std::unordered_map<std::string, std::shared_ptr<Mesh>> m_meshes;
    std::unordered_map<std::string, std::shared_ptr<OpenGL::Texture>> m_textures;
};
