#include "bufferlayout.h"

BufferLayout::BufferLayout()
    : _stride(0)
{
}

std::vector<LayoutElement> &BufferLayout::getElements()
{
    return _elements;
}

unsigned int BufferLayout::getStride() const
{
    return _stride;
}
