#pragma once

#include <glm/glm.hpp>

struct Block
{
    enum Type
    {
        Air,
        Grass,
        Dirt,
        Stone,
        Bedrock
    };

    Block(Type type = Type::Air) : _type(type) {}

    Type getType() const { return _type; }
    void setType(Type type) { _type = type; }

private:
    Type _type;
    int _hardness = 1;
    int _health = 100;
};