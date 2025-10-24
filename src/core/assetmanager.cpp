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

Mesh &AssetManager::loadMesh(const std::string &name, BufferLayout &layout)
{
    _meshes[name] = std::make_unique<Mesh>(layout);
    return *_meshes[name];
}

Mesh &AssetManager::getMesh(const std::string &name)
{
    return *_meshes[name];
}

Texture &AssetManager::loadTexture(const std::string &name, const std::string &path)
{
    _textures[name] = std::make_unique<Texture>();
    _textures[name]->loadImage(path.c_str());
    return *_textures[name];
}

Texture &AssetManager::getTexture(const std::string &name)
{
    return *_textures[name];
}

AssetManager *AssetManager::get()
{
    return _instance;
}