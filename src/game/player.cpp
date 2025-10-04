#include "player.h"

Player::Player()
{
    _moveSpeed = 5.0f;
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
    _transform.update();
}
