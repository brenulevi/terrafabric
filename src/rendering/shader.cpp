#include "shader.h"

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    auto _vertexShader = loadShader(vertexPath, GL_VERTEX_SHADER);
    auto _fragmentShader = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

    _id = glCreateProgram();
    glAttachShader(_id, _vertexShader);
    glAttachShader(_id, _fragmentShader);
    glLinkProgram(_id);

    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);

    int success;
    char infoLog[512];
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_id, 512, nullptr, infoLog);
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
    }
}

Shader::~Shader()
{
    glDeleteProgram(_id);
}

void Shader::bind()
{
    glUseProgram(_id);
}

unsigned int Shader::loadShader(const char *path, unsigned int type)
{
    std::fstream shaderFile(path);

    if (!shaderFile.is_open())
        throw std::runtime_error("Failed to open shader file: " + std::string(path));

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    std::string shaderCodeStr = shaderStream.str();
    const char *shaderCode = shaderCodeStr.c_str();

    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error("Shader compilation failed (" + std::string(path) + "): " + std::string(infoLog));
    }

    return shader;
}

int Shader::getUniformLocation(const std::string &name)
{
    if (_uniformLocations.find(name) == _uniformLocations.end())
    {
        int location = glGetUniformLocation(_id, name.c_str());
        if (location == -1)
            throw std::runtime_error("Uniform '" + name + "' not found in shader");
        _uniformLocations[name] = location;
    }
    return _uniformLocations[name];
}
