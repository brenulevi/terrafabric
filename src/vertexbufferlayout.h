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
        case GL_FLOAT:         return 4;
        case GL_UNSIGNED_INT:  return 4;
        case GL_UNSIGNED_BYTE: return 1;
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
    void push(int count)
    {
        static_assert(false, "Unsupported type in VertexBufferLayout::push");
    }

    template<>
    void push<float>(int count)
    {
        _elements.push_back({GL_FLOAT, count, GL_FALSE});
        _stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
    }

    template<>
    void push<unsigned int>(int count)
    {
        _elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        _stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void push<unsigned char>(int count)
    {
        _elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        _stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement>& getElements() const { return _elements; }
    inline unsigned int getStride() const { return _stride; }

private:
    std::vector<VertexBufferElement> _elements;
    unsigned int _stride;
};