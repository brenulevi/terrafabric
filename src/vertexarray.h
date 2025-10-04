#pragma once

#include <glad/glad.h>

#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void bind();

    void addBuffer(VertexBuffer& vb, VertexBufferLayout& layout);

private:
    unsigned int _id;
};

    