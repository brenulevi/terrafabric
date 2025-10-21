#include "indexbuffer.h"

IndexBuffer::IndexBuffer()
    : _count(0)
{
    glGenBuffers(1, &_id);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &_id);
}

void IndexBuffer::setData(const unsigned int *data, unsigned int size)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    _count = size / sizeof(unsigned int);
    unbind();
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount() const
{
    return _count;
}