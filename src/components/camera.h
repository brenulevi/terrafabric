#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera
{
    float fov;
    float aspectRatio;
    float nearClip;
    float farClip;

    Camera();

    glm::mat4 getProjectionMatrix() const;
};