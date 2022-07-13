#pragma once

#define OVERRIDE_IF(CONDITION) OVERRIDE_IF_##CONDITION
#define OVERRIDE_IF_true override
#define OVERRIDE_IF_false

#define VIRTUAL_IF_NOT(CONDITION) VIRTUAL_IF_NOT_##CONDITION
#define VIRTUAL_IF_NOT_true
#define VIRTUAL_IF_NOT_false virtual

#define FIRST_GENERATED_BODY(CLASS_NAME) OBJECT_BODY(CLASS_NAME, false)
#define GENERATED_BODY(CLASS_NAME) OBJECT_BODY(CLASS_NAME, true)

#define OBJECT_BODY(CLASS_NAME, FIRST_ONE)\
    \
    public:\
    using This_class = CLASS_NAME;\
    \
    static std::string_view static_get_name() noexcept\
    {\
        return #CLASS_NAME;\
    }\
    \
    static Class_obj* static_class()\
    {\
        return Class::get<CLASS_NAME>();\
    }\
    \
    VIRTUAL_IF_NOT(FIRST_ONE) Class_obj* get_class() OVERRIDE_IF(FIRST_ONE)\
    {\
        return CLASS_NAME::static_class();\
    }\
    \
    private:
