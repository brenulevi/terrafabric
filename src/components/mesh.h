#pragma once

#include "rendering/vertexarray.h"
#include "rendering/vertexbuffer.h"
#include "rendering/indexbuffer.h"

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