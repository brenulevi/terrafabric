#pragma once

#include <unordered_map>
#include <string>

#include "rendering/shader.h"
#include "rendering/texture.h"

class ResourceManager
{
public:
    static void shutdown();

    static Shader* addShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    static Shader* getShader(const std::string& name);

    static Texture* addTexture(const std::string& name, const std::string& path);
    static Texture* getTexture(const std::string& name);

private:
    static std::unordered_map<std::string, Shader*> _shaders;
    static std::unordered_map<std::string, Texture*> _textures;
};