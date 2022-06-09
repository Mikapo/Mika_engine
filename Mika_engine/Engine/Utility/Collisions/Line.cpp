#include "Line.h"
#include "glm/geometric.hpp"

glm::vec3 Line::get_direction() const 
{ 
	return glm::normalize(m_end - m_start); 
}
