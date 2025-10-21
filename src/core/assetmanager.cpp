#include "assetmanager.h"

AssetManager* AssetManager::_instance = nullptr;

AssetManager::AssetManager()
{
    if(_instance)
        return;

    _instance = this;
}

Shader& AssetManager::loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath)
{
    _shaders[name] = std::make_unique<Shader>(vertexPath.c_str(), fragmentPath.c_str());
    return *_shaders[name];
}

Shader& AssetManager::getShader(const std::string &name)
{
    return *_shaders[name];
}

AssetManager *AssetManager::get()
{
    return _instance;
}