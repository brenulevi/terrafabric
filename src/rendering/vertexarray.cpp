#include "vertexarray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_id);
}

void VertexArray::setVertexBuffer(const VertexBuffer &vb, BufferLayout &layout)
{
    bind();
    vb.bind();

    unsigned int offset = 0;
    std::vector<LayoutElement>& elements = layout.getElements();
    unsigned int index = 0;
    for(auto& e : elements)
    {
        glVertexAttribPointer(index, e.count, e.type, e.normalized, layout.getStride(), (void*)offset);
        glEnableVertexAttribArray(index);
        offset += e.count * LayoutElement::getSizeByType(e.type);
        index++;
    }

    unbind();
    vb.unbind();
}

void VertexArray::bind() const
{
    glBindVertexArray(_id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}
