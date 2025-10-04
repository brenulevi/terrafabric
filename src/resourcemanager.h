#pragma once

#include <unordered_map>
#include <string>

#include "shader.h"
#include "vertexbufferlayout.h"

class ResourceManager
{
public:
    static void shutdown();

    static Shader* addShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    static Shader* getShader(const std::string& name);

private:
    static std::unordered_map<std::string, Shader*> _shaders;
};