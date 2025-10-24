#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "rendering/shader.h"
#include "rendering/mesh.h"
#include "rendering/texture.h"

class AssetManager
{
public:
    AssetManager();

    Shader& loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
    Shader& getShader(const std::string& name);

    Mesh& loadMesh(const std::string& name, BufferLayout& layout);
    Mesh& getMesh(const std::string& name);

    Texture& loadTexture(const std::string& name, const std::string& path);
    Texture& getTexture(const std::string& name);

    static AssetManager* get();

private:
    std::unordered_map<std::string, std::unique_ptr<Shader>> _shaders;
    std::unordered_map<std::string, std::unique_ptr<Mesh>> _meshes;
    std::unordered_map<std::string, std::unique_ptr<Texture>> _textures;

    static AssetManager* _instance;
};