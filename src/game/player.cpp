#include "player.h"

#include "core/game.h"

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

    updateMovement(deltaTime);
    updateMouseLook();
    doRayCast();
}

void Player::onResize(int width, int height)
{
    _camera.aspectRatio = static_cast<float>(width) / static_cast<float>(height);
    _lastX = width / 2.0f;
    _lastY = height / 2.0f;
}

void Player::updateMovement(float deltaTime)
{
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
}

void Player::updateMouseLook()
{
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

void Player::doRayCast()
{
    RaycastHit hit;
    bool didHit = raycast(_transform.position, _transform.forward, 5.0f, &hit);

    if(!didHit)
        return;

    // idk yet how to do it

    // if(Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
    // {
    //     // Handle raycast hit
    //     // For example, log the hit position or interact with the object

    //     glm::ivec3 localPos = glm::ivec3(hit.position) - glm::ivec3(hit.chunk->getGlobalPosition());
    //     Game::getInstance()->getWorld()->breakBlock(hit.chunk, localPos);
    // }
    
    // if(Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
    // {
    //     glm::ivec3 localPos = glm::ivec3(hit.previousBlockPosition) - glm::ivec3(hit.chunk->getGlobalPosition());

    //     if(localPos.x < 0 || localPos.x >= CHUNK_SIZE_X ||
    //        localPos.y < 0 || localPos.y >= CHUNK_SIZE_Y ||
    //        localPos.z < 0 || localPos.z >= CHUNK_SIZE_Z)
    //         return;

    //     Game::getInstance()->getWorld()->placeBlock(hit.chunk, localPos, Block(Block::Type::Stone));
    // }
}
