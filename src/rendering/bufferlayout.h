#pragma once

#include <glad/glad.h>
#include <vector>

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

class BufferLayout
{
public:
    BufferLayout();

    template <typename T>
    void addLayoutElement(int count);

    std::vector<LayoutElement>& getElements();
    unsigned int getStride() const;

private:
    std::vector<LayoutElement> _elements;
    unsigned int _stride;
};

template <typename T>
inline void BufferLayout::addLayoutElement(int count)
{
    static_assert(false, "Unsupported type for BufferLayout");
}

template <>
inline void BufferLayout::addLayoutElement<float>(int count)
{
    _elements.push_back({ count, GL_FLOAT, false });
    _stride += count * sizeof(float);
}
