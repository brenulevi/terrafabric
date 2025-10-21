#pragma once

#include <glad/glad.h>

#include "vertexbuffer.h"
#include "bufferlayout.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void setVertexBuffer(const VertexBuffer& vb, BufferLayout& layout);

    void bind() const;
    void unbind() const;

private:
    unsigned int _id;
};