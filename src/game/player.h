#pragma once

#include <glm/glm.hpp>

#include "rendering/transform.h"
#include "rendering/camera.h"
#include "core/input.h"

class Player
{
public:
    Player();
    ~Player();

    void update(float deltaTime);

    void onResize(int width, int height);

    inline void setPosition(const glm::vec3 &position) { _transform.position = position; }
    inline void setRotation(const glm::vec3 &rotation) { _transform.rotation = rotation; }
    inline void setSpeed(float speed) { _moveSpeed = speed; }

    inline Transform& getTransform() { return _transform; }
    inline Camera& getCamera() { return _camera; }
    inline float getSpeed() { return _moveSpeed; }

private:
    Transform _transform;
    Camera _camera;

    float _moveSpeed;
    float _sensitivity;
    float _lastX;
    float _lastY;
};