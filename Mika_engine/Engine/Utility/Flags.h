#pragma once

#include <concepts>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace MEngine
{
    template <typename T>
    concept Flag_concept = std::is_enum_v<T> && std::is_unsigned_v<std::underlying_type_t<T>>;

    template <Flag_concept Flag_enum, std::unsigned_integral Underlying = uint64_t>
    class Flags
    {
    public:
        void add_flag(Flag_enum flag)
        {
            m_flags |= cast_flag_to_int(flag);
        }

        void remove_flag(Flag_enum flag)
        {
            m_flags &= ~cast_flag_to_int(flag);
        }

        bool has_flag(Flag_enum flag) const noexcept
        {
            return (m_flags & cast_flag_to_int(flag)) != 0;
        }

    private:
        static Underlying cast_flag_to_int(Flag_enum flag)
        {
            using Enum_underlying = std::underlying_type_t<Flag_enum>;

            Enum_underlying value = static_cast<Enum_underlying>(flag);

#ifdef _DEBUG
            if (value > std::numeric_limits<Underlying>::max())
                throw std::length_error("Invalid flag");
#endif

            return static_cast<Underlying>(value);
        }

        Underlying m_flags = 0;
    };
} // namespace MEngine
