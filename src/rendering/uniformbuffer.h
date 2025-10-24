#pragma once

#include <glad/glad.h>

class UniformBuffer
{
public:
    UniformBuffer(unsigned int size, unsigned int bindingPoint);
    ~UniformBuffer();

    void setData(unsigned int offset, unsigned int size, const void* data);

private:
    unsigned int _id;
};