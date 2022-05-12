#pragma once

#include "Objects/Object.h"
#include "glm/mat4x4.hpp"
#include "Rendering/Buffers/Buffers.h"
#include "Rendering/Shading/Material.h"
#include <memory>
#include <future>


class Shader;
class Mesh : public Object
{
public:
	void set_material(Material new_material);
	Material get_material() const;
	void set_buffers(std::shared_ptr<Buffers> buffers);
	std::shared_ptr<Buffers> get_buffers() const;

private:
	Material m_material;
	std::shared_ptr<Buffers> m_buffers;
};

