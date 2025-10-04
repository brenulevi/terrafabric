#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/resourcemanager.h"
#include "rendering/transform.h"
#include "rendering/camera.h"
#include "rendering/mesh.h"
#include "rendering/uniformbuffer.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear();

    void setView(Transform& transform, Camera& camera);

    void drawChunk(const glm::vec3& globalPosition, Mesh* mesh);

    void setViewport(int x, int y, int width, int height);

    void onResize(int width, int height);

private:
    UniformBuffer* _matricesUBO;
};