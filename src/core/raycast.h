#pragma once

#include "game/block.h"
#include "game/chunk.h"

struct RaycastHit
{
    glm::vec3 position;
    glm::vec3 previousBlockPosition;
    Block* block;
    Chunk* chunk;
    float distance;
};

bool raycast(const glm::vec3& origin, const glm::vec3& direction, float maxDistance, RaycastHit* outHit);