#pragma once

#define GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, CONST, A, B)                                                                  \
    vec<2, T, Q> A##B() CONST                                                                                          \
    {                                                                                                                  \
        return vec<2, T, Q>(this->A, this->B);                                                                         \
    }

#define GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, CONST, A, B, C)                                                               \
    vec<3, T, Q> A##B##C() CONST                                                                                       \
    {                                                                                                                  \
        return vec<3, T, Q>(this->A, this->B, this->C);                                                                \
    }

#define GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, CONST, A, B, C, D)                                                            \
    vec<4, T, Q> A##B##C##D() CONST                                                                                    \
    {                                                                                                                  \
        return vec<4, T, Q>(this->A, this->B, this->C, this->D);                                                       \
    }

#define GLM_SWIZZLE_GEN_VEC2_ENTRY_DEF(T, P, L, CONST, A, B)                                                           \
    template <typename T>                                                                                              \
    vec<L, T, Q> vec<L, T, Q>::A##B() CONST                                                                            \
    {                                                                                                                  \
        return vec<2, T, Q>(this->A, this->B);                                                                         \
    }

#define GLM_SWIZZLE_GEN_VEC3_ENTRY_DEF(T, P, L, CONST, A, B, C)                                                        \
    template <typename T>                                                                                              \
    vec<3, T, Q> vec<L, T, Q>::A##B##C() CONST                                                                         \
    {                                                                                                                  \
        return vec<3, T, Q>(this->A, this->B, this->C);                                                                \
    }

#define GLM_SWIZZLE_GEN_VEC4_ENTRY_DEF(T, P, L, CONST, A, B, C, D)                                                     \
    template <typename T>                                                                                              \
    vec<4, T, Q> vec<L, T, Q>::A##B##C##D() CONST                                                                      \
    {                                                                                                                  \
        return vec<4, T, Q>(this->A, this->B, this->C, this->D);                                                       \
    }

#define GLM_MUTABLE

#define GLM_SWIZZLE_GEN_REF2_FROM_VEC2_SWIZZLE(T, P, A, B)                                                             \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, 2, GLM_MUTABLE, A, B)                                                             \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, 2, GLM_MUTABLE, B, A)

#define GLM_SWIZZLE_GEN_REF_FROM_VEC2(T, P)                                                                            \
    GLM_SWIZZLE_GEN_REF2_FROM_VEC2_SWIZZLE(T, P, x, y)                                                                 \
    GLM_SWIZZLE_GEN_REF2_FROM_VEC2_SWIZZLE(T, P, r, g)                                                                 \
    GLM_SWIZZLE_GEN_REF2_FROM_VEC2_SWIZZLE(T, P, s, t)

#define GLM_SWIZZLE_GEN_REF2_FROM_VEC3_SWIZZLE(T, P, A, B, C)                                                          \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, C, B)

#define GLM_SWIZZLE_GEN_REF3_FROM_VEC3_SWIZZLE(T, P, A, B, C)                                                          \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, GLM_MUTABLE, A, B, C)                                                             \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, GLM_MUTABLE, A, C, B)                                                             \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, GLM_MUTABLE, B, A, C)                                                             \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, GLM_MUTABLE, B, C, A)                                                             \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, GLM_MUTABLE, C, A, B)                                                             \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, GLM_MUTABLE, C, B, A)

#define GLM_SWIZZLE_GEN_REF_FROM_VEC3_COMP(T, P, A, B, C)                                                              \
    GLM_SWIZZLE_GEN_REF3_FROM_VEC3_SWIZZLE(T, P, A, B, C)                                                              \
    GLM_SWIZZLE_GEN_REF2_FROM_VEC3_SWIZZLE(T, P, A, B, C)

#define GLM_SWIZZLE_GEN_REF_FROM_VEC3(T, P)                                                                            \
    GLM_SWIZZLE_GEN_REF_FROM_VEC3_COMP(T, P, x, y, z)                                                                  \
    GLM_SWIZZLE_GEN_REF_FROM_VEC3_COMP(T, P, r, g, b)                                                                  \
    GLM_SWIZZLE_GEN_REF_FROM_VEC3_COMP(T, P, s, t, p)

#define GLM_SWIZZLE_GEN_REF2_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)                                                       \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, GLM_MUTABLE, D, C)

#define GLM_SWIZZLE_GEN_REF3_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)                                                       \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , A, B, C)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , A, B, D)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , A, C, B)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , A, C, D)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , A, D, B)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , A, D, C)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , B, A, C)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , B, A, D)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , B, C, A)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , B, C, D)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , B, D, A)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , B, D, C)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , C, A, B)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , C, A, D)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , C, B, A)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , C, B, D)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , C, D, A)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , C, D, B)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , D, A, B)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , D, A, C)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , D, B, A)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , D, B, C)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , D, C, A)                                                                        \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, , D, C, B)

#define GLM_SWIZZLE_GEN_REF4_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)                                                       \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , A, C, B, D)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , A, C, D, B)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , A, D, B, C)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , A, D, C, B)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , A, B, D, C)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , A, B, C, D)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , B, C, A, D)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , B, C, D, A)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , B, D, A, C)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , B, D, C, A)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , B, A, D, C)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , B, A, C, D)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , C, B, A, D)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , C, B, D, A)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , C, D, A, B)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , C, D, B, A)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , C, A, D, B)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , C, A, B, D)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , D, C, B, A)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , D, C, A, B)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , D, A, B, C)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , D, A, C, B)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , D, B, A, C)                                                                     \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, , D, B, C, A)

#define GLM_SWIZZLE_GEN_REF_FROM_VEC4_COMP(T, P, A, B, C, D)                                                           \
    GLM_SWIZZLE_GEN_REF2_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)                                                           \
    GLM_SWIZZLE_GEN_REF3_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)                                                           \
    GLM_SWIZZLE_GEN_REF4_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)

#define GLM_SWIZZLE_GEN_REF_FROM_VEC4(T, P)                                                                            \
    GLM_SWIZZLE_GEN_REF_FROM_VEC4_COMP(T, P, x, y, z, w)                                                               \
    GLM_SWIZZLE_GEN_REF_FROM_VEC4_COMP(T, P, r, g, b, a)                                                               \
    GLM_SWIZZLE_GEN_REF_FROM_VEC4_COMP(T, P, s, t, p, q)

#define GLM_SWIZZLE_GEN_VEC2_FROM_VEC2_SWIZZLE(T, P, A, B)                                                             \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, A, A)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, A, B)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, B, A)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, B, B)

#define GLM_SWIZZLE_GEN_VEC3_FROM_VEC2_SWIZZLE(T, P, A, B)                                                             \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, A, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, A, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, B, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, B, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, A, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, A, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, B, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, B, B)

#define GLM_SWIZZLE_GEN_VEC4_FROM_VEC2_SWIZZLE(T, P, A, B)                                                             \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, B, B)

#define GLM_SWIZZLE_GEN_VEC_FROM_VEC2_COMP(T, P, A, B)                                                                 \
    GLM_SWIZZLE_GEN_VEC2_FROM_VEC2_SWIZZLE(T, P, A, B)                                                                 \
    GLM_SWIZZLE_GEN_VEC3_FROM_VEC2_SWIZZLE(T, P, A, B)                                                                 \
    GLM_SWIZZLE_GEN_VEC4_FROM_VEC2_SWIZZLE(T, P, A, B)

#define GLM_SWIZZLE_GEN_VEC_FROM_VEC2(T, P)                                                                            \
    GLM_SWIZZLE_GEN_VEC_FROM_VEC2_COMP(T, P, x, y)                                                                     \
    GLM_SWIZZLE_GEN_VEC_FROM_VEC2_COMP(T, P, r, g)                                                                     \
    GLM_SWIZZLE_GEN_VEC_FROM_VEC2_COMP(T, P, s, t)

#define GLM_SWIZZLE_GEN_VEC2_FROM_VEC3_SWIZZLE(T, P, A, B, C)                                                          \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, A, A)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, A, B)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, A, C)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, B, A)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, B, B)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, B, C)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, C, A)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, C, B)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, C, C)

#define GLM_SWIZZLE_GEN_VEC3_FROM_VEC3_SWIZZLE(T, P, A, B, C)                                                          \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, A, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, A, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, A, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, B, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, B, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, B, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, C, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, C, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, C, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, A, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, A, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, A, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, B, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, B, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, B, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, C, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, C, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, C, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, A, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, A, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, A, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, B, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, B, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, B, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, C, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, C, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, C, C)

#define GLM_SWIZZLE_GEN_VEC4_FROM_VEC3_SWIZZLE(T, P, A, B, C)                                                          \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, C, C)

#define GLM_SWIZZLE_GEN_VEC_FROM_VEC3_COMP(T, P, A, B, C)                                                              \
    GLM_SWIZZLE_GEN_VEC2_FROM_VEC3_SWIZZLE(T, P, A, B, C)                                                              \
    GLM_SWIZZLE_GEN_VEC3_FROM_VEC3_SWIZZLE(T, P, A, B, C)                                                              \
    GLM_SWIZZLE_GEN_VEC4_FROM_VEC3_SWIZZLE(T, P, A, B, C)

#define GLM_SWIZZLE_GEN_VEC_FROM_VEC3(T, P)                                                                            \
    GLM_SWIZZLE_GEN_VEC_FROM_VEC3_COMP(T, P, x, y, z)                                                                  \
    GLM_SWIZZLE_GEN_VEC_FROM_VEC3_COMP(T, P, r, g, b)                                                                  \
    GLM_SWIZZLE_GEN_VEC_FROM_VEC3_COMP(T, P, s, t, p)

#define GLM_SWIZZLE_GEN_VEC2_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)                                                       \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, A, A)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, A, B)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, A, C)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, A, D)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, B, A)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, B, B)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, B, C)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, B, D)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, C, A)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, C, B)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, C, C)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, C, D)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, D, A)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, D, B)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, D, C)                                                                      \
    GLM_SWIZZLE_GEN_VEC2_ENTRY(T, P, const, D, D)

#define GLM_SWIZZLE_GEN_VEC3_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)                                                       \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, A, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, A, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, A, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, A, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, B, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, B, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, B, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, B, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, C, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, C, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, C, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, C, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, D, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, D, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, D, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, A, D, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, A, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, A, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, A, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, A, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, B, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, B, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, B, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, B, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, C, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, C, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, C, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, C, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, D, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, D, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, D, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, B, D, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, A, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, A, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, A, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, A, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, B, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, B, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, B, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, B, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, C, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, C, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, C, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, C, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, D, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, D, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, D, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, C, D, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, A, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, A, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, A, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, A, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, B, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, B, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, B, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, B, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, C, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, C, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, C, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, C, D)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, D, A)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, D, B)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, D, C)                                                                   \
    GLM_SWIZZLE_GEN_VEC3_ENTRY(T, P, const, D, D, D)

#define GLM_SWIZZLE_GEN_VEC4_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)                                                       \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, A, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, B, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, C, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, A, D, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, A, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, B, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, C, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, B, D, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, A, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, B, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, C, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, C, D, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, A, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, B, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, C, D, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, A, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, A, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, A, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, A, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, B, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, B, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, B, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, B, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, C, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, C, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, C, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, C, D)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, D, A)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, D, B)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, D, C)                                                                \
    GLM_SWIZZLE_GEN_VEC4_ENTRY(T, P, const, D, D, D, D)

#define GLM_SWIZZLE_GEN_VEC_FROM_VEC4_COMP(T, P, A, B, C, D)                                                           \
    GLM_SWIZZLE_GEN_VEC2_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)                                                           \
    GLM_SWIZZLE_GEN_VEC3_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)                                                           \
    GLM_SWIZZLE_GEN_VEC4_FROM_VEC4_SWIZZLE(T, P, A, B, C, D)

#define GLM_SWIZZLE_GEN_VEC_FROM_VEC4(T, P)                                                                            \
    GLM_SWIZZLE_GEN_VEC_FROM_VEC4_COMP(T, P, x, y, z, w)                                                               \
    GLM_SWIZZLE_GEN_VEC_FROM_VEC4_COMP(T, P, r, g, b, a)                                                               \
    GLM_SWIZZLE_GEN_VEC_FROM_VEC4_COMP(T, P, s, t, p, q)
