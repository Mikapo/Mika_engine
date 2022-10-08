#include "Class_obj.h"

namespace MEngine
{
    std::unordered_map<std::string_view, std::unique_ptr<Class_obj>> Class::m_classes;
}
