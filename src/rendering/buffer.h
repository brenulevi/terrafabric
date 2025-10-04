#pragma once

#include <glad/glad.h>

class Buffer
{
public:
    Buffer(GLenum type);
    ~Buffer();

    void bind();

    void setData(GLsizeiptr size, const void *data, GLenum usage);

private:
    GLenum _type;

protected:
    unsigned int _id;
};