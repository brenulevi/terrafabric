#pragma once

#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

class Mesh
{
public:
    Mesh(BufferLayout& layout);

    void setVertices(const void* vertices, unsigned int size);
    void setIndices(const unsigned int* indices, unsigned int size);

    void bind() const;
    void unbind() const;

    unsigned int getIndexCount() const;

private:
    VertexArray _va;
    IndexBuffer _ib;
    VertexBuffer _vb;
};