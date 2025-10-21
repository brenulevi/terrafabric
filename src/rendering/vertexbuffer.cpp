#include "vertexbuffer.h"

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &_id);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_id);
}

void VertexBuffer::setData(const void *data, unsigned int size)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    unbind();
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
