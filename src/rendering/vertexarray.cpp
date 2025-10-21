#include "vertexarray.h"

VertexArray::VertexArray()
    : _stride(0)
{
    glGenVertexArrays(1, &_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_id);
}

void VertexArray::setVertexBuffer(const VertexBuffer &vb)
{
    bind();
    vb.bind();

    unsigned int offset = 0;
    unsigned int index = 0;
    for(auto& e : _elements)
    {
        glVertexAttribPointer(index, e.count, e.type, e.normalized, _stride, (void*)offset);
        glEnableVertexAttribArray(index);
        offset += e.count * LayoutElement::getSizeByType(e.type);
        index++;
    }

    unbind();
    vb.unbind();
}

void VertexArray::bind()
{
    glBindVertexArray(_id);
}

void VertexArray::unbind()
{
    glBindVertexArray(0);
}
