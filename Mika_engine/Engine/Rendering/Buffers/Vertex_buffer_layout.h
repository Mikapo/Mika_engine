#pragma once

#include <vector>

#include "GL/glew.h"
#include "Vertex_buffer.h"

struct Vertex_buffer_elements
{
    Vertex_buffer_elements(uint32_t type, int32_t count, unsigned char normalized)
        : m_type(type), m_count(count), m_normalized(normalized)
    {
    }

    uint32_t get_type() const { return m_type; }
    uint32_t get_count() const { return m_count; }
    unsigned char get_normalized() const { return m_normalized; }

    static int32_t get_size_of_type(uint32_t type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;

        case GL_UNSIGNED_INT:
            return 4;

        case GL_BYTE:
            return 1;
        default:
            return -1;
        }
    }

private:
    uint32_t m_type;
    int32_t m_count;
    unsigned char m_normalized;

};

class Vertex_buffer_layout
{
public:
    Vertex_buffer_layout() : m_stride(0) {}

    template <typename T>
    void push(uint32_t count)
    {
        static_assert(false);
    }
    template <>
    void push<float>(uint32_t count)
    {
        m_elements.emplace_back(GL_FLOAT, count, GL_FALSE);
        m_stride += count * Vertex_buffer_elements::get_size_of_type(GL_FLOAT);
    }
    template <>
    void push<uint32_t>(uint32_t count)
    {
        m_elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE);
        m_stride += count * Vertex_buffer_elements::get_size_of_type(GL_UNSIGNED_INT);
    }
    template <>
    void push<unsigned char>(uint32_t count)
    {
        m_elements.emplace_back(GL_UNSIGNED_BYTE, count, GL_TRUE);
        m_stride += count * Vertex_buffer_elements::get_size_of_type(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<Vertex_buffer_elements>& get_elements() const { return m_elements; }
    inline uint32_t get_stride() const { return m_stride; }

private:
    std::vector<Vertex_buffer_elements> m_elements;
    int32_t m_stride;
};
