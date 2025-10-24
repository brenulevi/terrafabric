#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "core/assetmanager.h"
#include "components/transform.h"
#include "components/camera.h"
#include "shader.h"
#include "mesh.h"
#include "uniformbuffer.h"
#include "texture.h"

class Renderer
{
public:
    Renderer();

    void clear();
    void beginFrame(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
    void drawCube(Transform& transform, Mesh& mesh, Texture& texture);
    void drawChunk(const glm::vec3& position, Mesh& mesh);

    void onResize(int width, int height);

private:
    std::unique_ptr<UniformBuffer> _matricesUBO;
};