#pragma once

#include "components/transform.h"
#include "components/camera.h"
#include "core/input.h"

class Player
{
public:
    Player();

    void update();

    Transform& getTransform();
    Camera& getCamera();
    glm::mat4 getViewMatrix() const;

private:
    Transform _transform;
    Camera _camera;

    float _speed;
};