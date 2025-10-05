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

    inline int getWidth() const { return _width; }
    inline int getHeight() const { return _height; }

private:
    unsigned int _id;
    int _width;
    int _height;
    int _channels;
};