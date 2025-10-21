#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "rendering/shader.h"

class AssetManager
{
public:
    AssetManager();

    Shader& loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    Shader& getShader(const std::string& name);

    static AssetManager* get();

private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> _shaders;

    static AssetManager* _instance;
};