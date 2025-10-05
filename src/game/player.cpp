#include "player.h"

Player::Player()
{
    _moveSpeed = 25.0f;
    _sensitivity = 0.1f;
    _lastX = 400.0f; // Assuming initial mouse position at the center of an 800px wide window
    _lastY = 300.0f; // Assuming initial mouse position at the center of a 600px high window
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
    _transform.update();

    glm::vec3 moveDirection(0.0f);

    if(Input::isKeyHeld(GLFW_KEY_W))
        moveDirection += _transform.forward;
    if(Input::isKeyHeld(GLFW_KEY_S))
        moveDirection -= _transform.forward;
    if(Input::isKeyHeld(GLFW_KEY_A))
        moveDirection -= _transform.right;
    if(Input::isKeyHeld(GLFW_KEY_D))
        moveDirection += _transform.right;
    if(Input::isKeyHeld(GLFW_KEY_SPACE))
        moveDirection += glm::vec3(0.0f, 1.0f, 0.0f);
    if(Input::isKeyHeld(GLFW_KEY_LEFT_SHIFT))
        moveDirection -= glm::vec3(0.0f, 1.0f, 0.0f);

    if(glm::length(moveDirection) > 0.0f)
        moveDirection = glm::normalize(moveDirection);

    _transform.position += moveDirection * _moveSpeed * deltaTime;

    float mouseX = Input::getMouseX();
    float mouseY = Input::getMouseY();

    float offsetX = mouseX - _lastX;
    float offsetY = _lastY - mouseY; // Reversed since y-coordinates go from bottom to top

    _lastX = mouseX;
    _lastY = mouseY;

    offsetX *= _sensitivity;
    offsetY *= _sensitivity;

    _transform.rotation.y += offsetX;
    _transform.rotation.x += offsetY;

    if(_transform.rotation.x > 89.0f)
        _transform.rotation.x = 89.0f;
    else if(_transform.rotation.x < -89.0f)
        _transform.rotation.x = -89.0f;
}

void Player::onResize(int width, int height)
{
    _camera.aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    _lastX = width / 2.0f;
    _lastY = height / 2.0f;
}
