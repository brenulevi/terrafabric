#include "buffer.h"

Buffer::Buffer(GLenum type)
    : _type(type)
{
    glGenBuffers(1, &_id);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &_id);
}

void Buffer::bind()
{
    glBindBuffer(_type, _id);
}

void Buffer::setData(GLsizeiptr size, const void *data, GLenum usage)
{
    bind();
    glBufferData(_type, size, data, usage);
}
