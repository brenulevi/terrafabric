#pragma once

#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void setVertices(const void* vertices, unsigned int size);
    void setIndices(const unsigned int* indices, unsigned int size);

    void bind();
    void unbind();

private:
    VertexArray _va;
    IndexBuffer _ib;
    VertexBuffer _vb;
};