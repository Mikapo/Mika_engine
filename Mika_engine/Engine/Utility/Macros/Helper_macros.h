#pragma once

#include "boost/preprocessor.hpp"

#define ENUM_TO_STRING_CASE(i, name, enumator)                                                                         \
    case name::enumator:                                                                                               \
        return BOOST_PP_STRINGIZE(enumator);

#define DECLARE_ENUM(name, type, enumators)                                                                            \
    enum class name : type                                                                                             \
    {                                                                                                                  \
        BOOST_PP_SEQ_ENUM(enumators)                                                                                   \
    };                                                                                                                 \
    std::string_view enum_to_string(name value)                                                                        \
    {                                                                                                                  \
        switch (value)                                                                                                 \
        {                                                                                                              \
            BOOST_PP_SEQ_FOR_EACH(ENUM_TO_STRING_CASE, test, enumators)                                                \
                                                                                                                       \
        default:                                                                                                       \
            return "unkown";                                                                                           \
        }                                                                                                              \
    }
