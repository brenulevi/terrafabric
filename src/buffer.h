#pragma once

#include <glad/glad.h>

class Buffer
{
public:
    Buffer(GLenum type);
    ~Buffer();

    void bind();

    void setData(GLsizeiptr size, const void* data, GLenum usage);

private:
    unsigned int _id;
    GLenum _type;
};