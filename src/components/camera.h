#pragma once

#include <glm/glm.hpp>

struct Camera
{
    Camera();

    float fov;
    float aspectRatio;
    float nearClip;
    float farClip;

    glm::mat4 getProjectionMatrix() const;
};