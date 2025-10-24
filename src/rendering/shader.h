#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

class Shader
{
public:
    Shader(const char* vPath, const char* fPath);
    ~Shader();

    void setInt(const std::string& name, int value);
    void setMat4(const std::string& name, const float* matrix);

    void bind() const;
    void unbind() const;

private:
    unsigned int createAndCompileShader(const char* path, GLenum type);
    int getUniformLocation(const std::string& name);

private:
    unsigned int _id;
    std::unordered_map<std::string, int> _uniformLocationCache;
};