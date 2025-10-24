#include "transform.h"

Transform::Transform()
    : position(0.0f, 0.0f, 0.0f)
    , rotation(0.0f, 0.0f, 0.0f)
    , scale(1.0f, 1.0f, 1.0f)
    , forward(0.0f, 0.0f, -1.0f)
    , up(0.0f, 1.0f, 0.0f)
    , right(1.0f, 0.0f, 0.0f)
{
}

void Transform::updateVectors()
{
    forward = glm::normalize(glm::vec3(
        cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x)),
        sin(glm::radians(rotation.x)),
        sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x))
    ));
    right = glm::normalize(glm::cross(forward, up));
    up = glm::normalize(glm::cross(right, forward));
}

glm::mat4 Transform::getModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}
