#pragma once

#include <memory>

#include "core/assetmanager.h"
#include "components/transform.h"
#include "rendering/mesh.h"
#include "rendering/texture.h"

class Cube
{
public:
    Cube();

    void update();

    Transform& getTransform();
    Mesh& getMesh();
    Texture& getTexture();

private:
    Transform _transform;
    std::unique_ptr<Mesh> _mesh;
    Texture& _texture;
};