#pragma once

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void bind();

private:
    unsigned int loadShader(const char* path, unsigned int type);


private:
    unsigned int _id;
};