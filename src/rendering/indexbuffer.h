#pragma once

#include <glad/glad.h>

class IndexBuffer
{
public:
    IndexBuffer();
    ~IndexBuffer();

    void setData(const unsigned int* data, unsigned int size);

    void bind() const;
    void unbind() const;

    unsigned int getCount() const;

private:
    unsigned int _id;
    unsigned int _count;
};