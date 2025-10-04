#pragma once

#include "vertexarray.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"

struct Mesh
{
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;

    Mesh(VertexBufferLayout& layout)
    {
        vertexArray.addBuffer(vertexBuffer, layout);
    }
};