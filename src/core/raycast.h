#pragma once

#include <glm/glm.hpp>

#include "game/block.h"

struct RaycastHit
{
    glm::ivec3 blockPos;   // coordenadas do bloco atingido (inteiro)
    glm::vec3 hitPoint;    // ponto exato de impacto em world coords
    glm::vec3 faceNormal;  // normal da face atingida (unitária: (±1,0,0), (0,±1,0) ou (0,0,±1))
    float distance;        // distância desde origin até hitPoint
};

class Raycast
{
public:
    // DDA algorithm for raycasting in a voxel grid
    static bool cast(const glm::vec3& start, const glm::vec3& direction, float maxDistance, RaycastHit& hitInfo);
};