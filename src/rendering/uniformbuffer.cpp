#include "uniformbuffer.h"

UniformBuffer::UniformBuffer(unsigned int size, unsigned int bindingPoint)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_UNIFORM_BUFFER, _id);
    glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, _id);
}

UniformBuffer::~UniformBuffer()
{
    glDeleteBuffers(1, &_id);
}

void UniformBuffer::setData(unsigned int offset, unsigned int size, const void *data)
{
    glBindBuffer(GL_UNIFORM_BUFFER, _id);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
