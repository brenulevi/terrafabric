#include "resourcemanager.h"

std::unordered_map<std::string, Shader*> ResourceManager::_shaders;

void ResourceManager::shutdown()
{
    for (auto& pair : _shaders)
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
