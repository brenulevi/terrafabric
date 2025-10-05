#pragma once

#include <glad/glad.h>
#include <string>
#include <stdexcept>

class Texture
{
public:
    Texture(const char* path);
    ~Texture();

    void bind(unsigned int slot = 0);

    void setFiltering(GLenum minFilter, GLenum magFilter);
    void setWrapMode(GLenum wrapS, GLenum wrapT);

private:
    unsigned int _id;
    int _width;
    int _height;
    int _channels;
};