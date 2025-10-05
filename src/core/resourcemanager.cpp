#include "resourcemanager.h"

std::unordered_map<std::string, Shader*> ResourceManager::_shaders;
std::unordered_map<std::string, Texture*> ResourceManager::_textures;
std::unordered_map<std::string, Mesh*> ResourceManager::_meshes;

void ResourceManager::shutdown()
{
    for (auto& pair : _shaders)
    {
        delete pair.second;
    }

    for (auto& pair : _textures)
    {
        delete pair.second;
    }
}

Shader* ResourceManager::addShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath)
{
    _shaders[name] = new Shader(vertexPath.c_str(), fragmentPath.c_str());
    return _shaders[name];
}

Shader* ResourceManager::getShader(const std::string &name)
{
    if (_shaders.find(name) != _shaders.end())
    {
        return _shaders[name];
    }
    return nullptr;
}

Texture *ResourceManager::addTexture(const std::string &name, const std::string &path)
{
    _textures[name] = new Texture(path.c_str());
    return _textures[name];
}

Texture *ResourceManager::getTexture(const std::string &name)
{
    if (_textures.find(name) != _textures.end())
    {
        return _textures[name];
    }
    return nullptr;
}

Mesh *ResourceManager::addMesh(const std::string &name, VertexBufferLayout &layout)
{
    _meshes[name] = new Mesh(layout);
    return _meshes[name];
}

Mesh *ResourceManager::getMesh(const std::string &name)
{
    if (_meshes.find(name) != _meshes.end())
    {
        return _meshes[name];
    }
    return nullptr;
}
