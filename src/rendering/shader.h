#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
public:
    Shader(const char* vPath, const char* fPath);
    ~Shader();

    void bind();
    void unbind();

private:
    unsigned int createAndCompileShader(const char* path, GLenum type);

private:
    unsigned int _id;
};