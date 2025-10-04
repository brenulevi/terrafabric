#include "vertexarray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_id);
}

void VertexArray::bind()
{
    glBindVertexArray(_id);
}

void VertexArray::addBuffer(VertexBuffer &vb, VertexBufferLayout &layout)
{
    glBindVertexArray(_id);
    vb.bind();

    auto& elements = layout.getElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, element.normalized ? GL_TRUE : GL_FALSE, layout.getStride(), (const void*)offset);
        offset += element.count * VertexBufferElement::getSizeOfType(element.type);
    }
}
