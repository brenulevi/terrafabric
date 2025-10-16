#include "raycast.h"

#include "game.h"

bool Raycast::cast(const glm::vec3 &start, const glm::vec3 &direction, float maxDistance, RaycastHit &hitInfo)
{
    const float EPS = 1e-6f;
    glm::vec3 dir = glm::normalize(direction);

    // Se direção inválida
    if (glm::length(dir) < EPS) return false;

    // Posição inicial no espaço de blocos (floor -> bloco contendo o ponto)
    glm::ivec3 voxel(
        static_cast<int>(std::floor(start.x)),
        static_cast<int>(std::floor(start.y)),
        static_cast<int>(std::floor(start.z))
    );

    // Se ponto inicial está dentro de bloco sólido, podemos retornar imediatamente (opcional)
    Block* block = Game::getInstance()->getWorld()->getBlockAt(voxel);
    if (block && block->type != Block::Air){
        hitInfo.blockPos = voxel;
        hitInfo.hitPoint = start;
        hitInfo.faceNormal = glm::vec3(0.0f); // dentro do bloco — sem normal clara
        hitInfo.distance = 0.0f;
        return true;
    }

    // Step por eixo: +1 ou -1
    glm::ivec3 step(
        dir.x > 0 ? 1 : -1,
        dir.y > 0 ? 1 : -1,
        dir.z > 0 ? 1 : -1
    );

    // tMax: distância 't' até o primeiro plano da grade ao longo de cada eixo
    glm::vec3 tMax;
    glm::vec3 tDelta;

    auto calcT = [&](float originCoord, float dirCoord, int voxelCoord)->std::pair<float,float> {
        if (std::abs(dirCoord) < EPS) {
            return { std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity() };
        } else {
            float nextBoundary = (dirCoord > 0.0f) ? (static_cast<float>(voxelCoord) + 1.0f) : (static_cast<float>(voxelCoord));
            float tmax = (nextBoundary - originCoord) / dirCoord; // t até o próximo plano
            float tdelta = 1.0f / std::abs(dirCoord); // distância entre planos consecutivos no mesmo eixo
            return { tmax, tdelta };
        }
    };

    auto rx = calcT(start.x, dir.x, voxel.x);
    auto ry = calcT(start.y, dir.y, voxel.y);
    auto rz = calcT(start.z, dir.z, voxel.z);

    tMax.x = rx.first;
    tDelta.x = rx.second;
    tMax.y = ry.first;
    tDelta.y = ry.second;
    tMax.z = rz.first;
    tDelta.z = rz.second;

    // t atual (distância ao longo do raio)
    float t = 0.0f;
    // segurança: número máximo de passos (evita loops infinitos em casos estranhos)
    const int MAX_STEPS = 1024 * 16;

    for (int i = 0; i < MAX_STEPS; ++i) {
        // escolher qual eixo avançar (menor tMax)
        if (tMax.x < tMax.y) {
            if (tMax.x < tMax.z) {
                // avançar X
                voxel.x += step.x;
                t = tMax.x;
                tMax.x += tDelta.x;
                hitInfo.faceNormal = glm::vec3(-step.x, 0.0f, 0.0f); // normal aponta contra o step para identificar face
            } else {
                // avançar Z
                voxel.z += step.z;
                t = tMax.z;
                tMax.z += tDelta.z;
                hitInfo.faceNormal = glm::vec3(0.0f, 0.0f, -step.z);
            }
        } else {
            if (tMax.y < tMax.z) {
                // avançar Y
                voxel.y += step.y;
                t = tMax.y;
                tMax.y += tDelta.y;
                hitInfo.faceNormal = glm::vec3(0.0f, -step.y, 0.0f);
            } else {
                // avançar Z
                voxel.z += step.z;
                t = tMax.z;
                tMax.z += tDelta.z;
                hitInfo.faceNormal = glm::vec3(0.0f, 0.0f, -step.z);
            }
        }

        if (t > maxDistance) break;

        // verificar bloco atual
        Block* block = Game::getInstance()->getWorld()->getBlockAt(voxel);
        if (block && block->type != Block::Air) {
            hitInfo.blockPos = voxel;
            hitInfo.distance = t;
            hitInfo.hitPoint = start + dir * t;
            // faceNormal já setada ao avançar
            return true;
        }
    }

    return false;
}