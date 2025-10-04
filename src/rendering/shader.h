#pragma once

#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <unordered_map>

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void bind();

    inline void setUniformMat4(const std::string& name, const float* value) { glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value); }

private:
    unsigned int loadShader(const char* path, unsigned int type);
    int getUniformLocation(const std::string& name);

private:
    unsigned int _id;
    std::unordered_map<std::string, int> _uniformLocations;
};