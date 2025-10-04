#pragma once

#include "buffer.h"

class UniformBuffer : public Buffer
{
public:
    UniformBuffer(unsigned int size, GLuint binding)
        : Buffer(GL_UNIFORM_BUFFER), _binding(binding)
    {
        setData(size, nullptr, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, _id);
    }

    void setSubData(GLintptr offset, GLsizeiptr size, const void *data)
    {
        bind();
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    }

private:
    GLuint _binding;
};