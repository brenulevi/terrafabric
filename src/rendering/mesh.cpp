#include "mesh.h"

Mesh::Mesh(BufferLayout &layout)
{
    _va.setVertexBuffer(_vb, layout);
}

void Mesh::setVertices(const void *vertices, unsigned int size)
{
    _vb.setData(vertices, size);
}

void Mesh::setIndices(const unsigned int *indices, unsigned int size)
{
    _ib.setData(indices, size);
}

void Mesh::bind() const
{
    _va.bind();
    _vb.bind();
    _ib.bind();
}

void Mesh::unbind() const
{
    _ib.unbind();
    _vb.unbind();
    _va.unbind();
}

unsigned int Mesh::getIndexCount() const
{
    return _ib.getCount();
}
