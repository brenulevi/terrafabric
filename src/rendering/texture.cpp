#include "texture.h"

Texture::Texture()
{
    glGenTextures(1, &_id);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_id);
}

void Texture::loadImage(const char *path)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &_width, &_height, &_channels, 4);
    if (!data)
    {
        std::cout << "Invalid texture path: " << path << std::endl;
        return;
    }
    
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
}

void Texture::setFiltering(GLenum minFilter, GLenum magFilter)
{
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setWrapping(GLenum wrapS, GLenum wrapT)
{
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
