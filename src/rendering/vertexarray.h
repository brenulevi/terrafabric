#pragma once

#include <glad/glad.h>
#include <vector>

#include "vertexbuffer.h"

struct LayoutElement
{
    int count;
    GLenum type;
    bool normalized;

    static unsigned int getSizeByType(GLenum type)
    {
        switch (type)
        {
        case GL_FLOAT: return sizeof(float);
        case GL_UNSIGNED_INT: return sizeof(unsigned int);
        }

        return 4;
    }
};

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    template <typename T>
    void addLayoutElement(int count);

    void setVertexBuffer(const VertexBuffer& vb);

    void bind();
    void unbind();

private:
    unsigned int _id;

    std::vector<LayoutElement> _elements;
    unsigned int _stride;
};

template <typename T>
inline void VertexArray::addLayoutElement(int count)
{
    static_assert(false);
}

template <>
inline void VertexArray::addLayoutElement<float>(int count)
{
    _elements.push_back({ count, GL_FLOAT, false });
    _stride += count * sizeof(float);
}
