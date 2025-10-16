#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "logging/logger.h"
#include "core/resourcemanager.h"
#include "components/transform.h"
#include "components/camera.h"
#include "components/mesh.h"
#include "rendering/uniformbuffer.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void clear();

    void setView(Transform& transform, Camera& camera);

    void drawChunk(const glm::vec3& globalPosition, Mesh* mesh);
    void drawSprite(const glm::vec2& position, const glm::vec2& size, float rotation, Texture* texture);
    void drawRay(const glm::vec3& start, const glm::vec3& direction, float length, const glm::vec3& color);

    void setViewport(int x, int y, int width, int height);
    void setPolygonMode(GLenum mode) { glPolygonMode(GL_FRONT_AND_BACK, mode); }

    void onResize(int width, int height);

private:
    UniformBuffer* _matricesUBO;
    UniformBuffer* _orthoUBO;
};