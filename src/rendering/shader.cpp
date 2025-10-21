#include "shader.h"

Shader::Shader(const char *vPath, const char *fPath)
{
    unsigned int VS = createAndCompileShader(vPath, GL_VERTEX_SHADER);
    unsigned int FS = createAndCompileShader(fPath, GL_FRAGMENT_SHADER);

    _id = glCreateProgram();
    glAttachShader(_id, VS);
    glAttachShader(_id, FS);
    glLinkProgram(_id);

    int success;
    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if(!success)
    {
        char log[512];
        glGetProgramInfoLog(_id, 512, nullptr, log);
        std::cout << log << std::endl;
    }

    glDeleteShader(VS);
    glDeleteShader(FS);
}

Shader::~Shader()
{
    glDeleteProgram(_id);
}

void Shader::bind()
{
    glUseProgram(_id);
}

void Shader::unbind()
{
    glUseProgram(0);
}

unsigned int Shader::createAndCompileShader(const char *path, GLenum type)
{
    unsigned int shader = glCreateShader(type);

    std::fstream shaderFile(path);

    if(!shaderFile.is_open())
    {
        std::cout << "Invalid shader path: " << path << std::endl;
    }

    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    std::string shaderStr = shaderStream.str();
    const char* shaderSource = shaderStr.c_str();

    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cout << log << std::endl;
    }

    return shader;
}
