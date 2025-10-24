#include "player.h"

Player::Player()
{
    _transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    _transform.rotation = glm::vec3(0.0f, -90.0f, 0.0f);

    _speed = 0.1f;
}

void Player::update()
{
    _transform.updateVectors();

    glm::vec3 moveDirection(0.0f);

    if(Input::get()->isKeyHeld(GLFW_KEY_W))
        moveDirection += _transform.forward;
    if(Input::get()->isKeyHeld(GLFW_KEY_S))
        moveDirection -= _transform.forward;

    moveDirection.y = 0.0f; // Prevent vertical movement

    if(Input::get()->isKeyHeld(GLFW_KEY_A))
        moveDirection -= _transform.right;
    if(Input::get()->isKeyHeld(GLFW_KEY_D))
        moveDirection += _transform.right;
    if(Input::get()->isKeyHeld(GLFW_KEY_SPACE))
        moveDirection += glm::vec3(0.0f, 1.0f, 0.0f);
    if(Input::get()->isKeyHeld(GLFW_KEY_LEFT_SHIFT))
        moveDirection -= glm::vec3(0.0f, 1.0f, 0.0f);

    if(glm::length(moveDirection) > 0.0f)
        moveDirection = glm::normalize(moveDirection);
        
    _transform.position += moveDirection * _speed;
}

Transform &Player::getTransform()
{
    return _transform;
}

Camera &Player::getCamera()
{
    return _camera;
}

glm::mat4 Player::getViewMatrix() const
{
    return glm::lookAt(_transform.position, _transform.position + _transform.forward, _transform.up);
}
