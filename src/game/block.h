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
    
    Type type;
};