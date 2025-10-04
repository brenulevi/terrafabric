#pragma once

#include "buffer.h"

class VertexBuffer : public Buffer
{
public:
    VertexBuffer()
        : Buffer(GL_ARRAY_BUFFER)
    {
    }
};