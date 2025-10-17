#include "raycast.h"

#include "game.h"

bool Raycast::DDACast(const glm::vec3 &start, const glm::vec3 &direction, float maxDistance, RaycastHit &hitInfo)
{
    const float EPS = 1e-6f;
    glm::vec3 dir = glm::normalize(direction);

    // Se direção inválida
    if (glm::length(dir) < EPS)
        return false;

    // Posição inicial ligeiramente dentro do raio para evitar fronteira exata
    glm::vec3 originSafe = start + dir * 1e-4f;

    // Bloco inicial
    glm::ivec3 voxel(
        (int)std::floor(originSafe.x),
        (int)std::floor(originSafe.y),
        (int)std::floor(originSafe.z));

    // Step em cada eixo
    glm::ivec3 step(
        dir.x > 0 ? 1 : -1,
        dir.y > 0 ? 1 : -1,
        dir.z > 0 ? 1 : -1);

    glm::vec3 tMax;
    glm::vec3 tDelta;

    auto calcT = [&](float originCoord, float dirCoord, int voxelCoord) -> std::pair<float, float>
    {
        if (std::abs(dirCoord) < EPS)
            return {std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()};

        float voxelBorder = (dirCoord > 0.0f)
                                ? (float(voxelCoord) + 1.0f)
                                : (float(voxelCoord)); // borda para onde estamos indo

        float tMax = (voxelBorder - originCoord) / dirCoord;
        float tDelta = 1.0f / std::abs(dirCoord);
        return {tMax, tDelta};
    };

    auto [tx, dx] = calcT(originSafe.x, dir.x, voxel.x);
    auto [ty, dy] = calcT(originSafe.y, dir.y, voxel.y);
    auto [tz, dz] = calcT(originSafe.z, dir.z, voxel.z);

    tMax = glm::vec3(tx, ty, tz);
    tDelta = glm::vec3(dx, dy, dz);

    // t atual (distância ao longo do raio)
    float t = 0.0f;
    // segurança: número máximo de passos (evita loops infinitos em casos estranhos)
    const int MAX_STEPS = 1024 * 16;

    for (int i = 0; i < MAX_STEPS; ++i)
    {
        // escolher qual eixo avançar (menor tMax)
        if (tMax.x < tMax.y)
        {
            if (tMax.x < tMax.z)
            {
                // avançar X
                voxel.x += step.x;
                t = tMax.x;
                tMax.x += tDelta.x;
                hitInfo.faceNormal = glm::vec3(-step.x, 0.0f, 0.0f); // normal aponta contra o step para identificar face
            }
            else
            {
                // avançar Z
                voxel.z += step.z;
                t = tMax.z;
                tMax.z += tDelta.z;
                hitInfo.faceNormal = glm::vec3(0.0f, 0.0f, -step.z);
            }
        }
        else
        {
            if (tMax.y < tMax.z)
            {
                // avançar Y
                voxel.y += step.y;
                t = tMax.y;
                tMax.y += tDelta.y;
                hitInfo.faceNormal = glm::vec3(0.0f, -step.y, 0.0f);
            }
            else
            {
                // avançar Z
                voxel.z += step.z;
                t = tMax.z;
                tMax.z += tDelta.z;
                hitInfo.faceNormal = glm::vec3(0.0f, 0.0f, -step.z);
            }
        }

        if (t > maxDistance)
            break;

        // verificar bloco atual
        Block *block = Game::getInstance()->getWorld()->getBlockAt(voxel);
        if (block && block->type != Block::Air)
        {
            hitInfo.blockPos = voxel;
            hitInfo.distance = t;
            hitInfo.hitPoint = start + dir * t;
            // faceNormal já setada ao avançar
            return true;
        }
    }

    return false;
}

bool Raycast::cast(const glm::vec3 &start, const glm::vec3 &direction, float maxDistance, RaycastHit &hitInfo)
{
    for(float t = 0.0f; t <= maxDistance; t += 0.1f)
    {
        glm::vec3 currentPos = start + direction * t;
        glm::ivec3 voxel(
            (int)std::floor(currentPos.x),
            (int)std::floor(currentPos.y),
            (int)std::floor(currentPos.z)
        );

        Block* block = Game::getInstance()->getWorld()->getBlockAt(voxel);
        if(block && block->type != Block::Air)
        {
            hitInfo.blockPos = voxel;
            hitInfo.hitPoint = currentPos;
            hitInfo.distance = t;
            // A normal da face não é calculada neste método simples
            hitInfo.faceNormal = glm::vec3(0.0f, 0.0f, 0.0f);
            return true;
        }
    }

    return false;
}
