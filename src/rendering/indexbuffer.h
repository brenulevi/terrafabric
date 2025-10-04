#pragma once

#include "buffer.h"

class IndexBuffer : public Buffer
{
public:
    IndexBuffer()
        : Buffer(GL_ELEMENT_ARRAY_BUFFER), _count(0) {}

    void setData(GLsizeiptr size, const unsigned int* data, GLenum usage)
    {
        Buffer::setData(size, data, usage);
        _count = size / sizeof(unsigned int);
    }
 
    inline unsigned int getCount() const { return _count; }

private:
    unsigned int _count;
};