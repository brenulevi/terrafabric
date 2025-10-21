#pragma once

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

class Texture
{
public:
    Texture();
    ~Texture();

    void loadImage(const char* path);

    void setFiltering(GLenum minFilter, GLenum magFilter);
    void setWrapping(GLenum wrapS, GLenum wrapT);

    void bind(unsigned int slot = 0) const;
    void unbind() const;

private:
    unsigned int _id;
    int _width;
    int _height;
    int _channels;
};

