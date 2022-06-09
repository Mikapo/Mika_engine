#pragma once

#define GENERATED_BODY(CLASS_NAME)\
\
public:\
using This_class = CLASS_NAME;\
\
static std::string_view static_get_name()\
{\
    return #CLASS_NAME;\
}\
\
static Class_obj* static_class()\
{\
    return Class::get<CLASS_NAME>();\
}\
\
virtual Class_obj* get_class()\
{\
    return CLASS_NAME::static_class();\
}
