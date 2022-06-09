#include "Collision.h"

#include "Datatypes/Min_max.h"
#include <stdexcept>

glm::vec3 Collision::get_origin() const
{ 
	return m_origin; 
}

void Collision::update(Transform transform) 
{ 
	throw std::runtime_error("should never be called"); 
}
