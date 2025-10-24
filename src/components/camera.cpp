#include "camera.h"

Camera::Camera()
    : fov(75.0f),
      aspectRatio(4.0f / 3.0f),
      nearClip(0.1f),
      farClip(1000.0f)
{
}

glm::mat4 Camera::getProjectionMatrix() const
{
    return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}