#pragma once

#include <glad/glad.h>
#include <vector>
#include <stdexcept>

struct VertexBufferElement
{
    unsigned int type;
    int count;
    bool normalized;

    static unsigned int getSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:         return sizeof(float);
        case GL_UNSIGNED_INT:  return sizeof(unsigned int);
        case GL_UNSIGNED_BYTE: return sizeof(unsigned char);
        }
        throw std::runtime_error("Unknown type in VertexBufferElement");
        return 0;
    }
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() : _stride(0) {}

    template<typename T>
    void push(int count);
    
    inline const std::vector<VertexBufferElement>& getElements() const { return _elements; }
    inline unsigned int getStride() const { return _stride; }

private:
    std::vector<VertexBufferElement> _elements;
    unsigned int _stride;
};

template <typename T>
inline void VertexBufferLayout::push(int count)
{
    static_assert(false, "Unsupported type in VertexBufferLayout::push");
}

template <>
inline void VertexBufferLayout::push<float>(int count)
{
    _elements.push_back({ GL_FLOAT, count, GL_FALSE });
    _stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}