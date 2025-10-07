#include "raycast.h"

#include "core/game.h"

bool raycast(const glm::vec3 &origin, const glm::vec3 &direction, float maxDistance, RaycastHit *outHit)
{
    glm::ivec3 current = glm::floor(origin);

    glm::vec3 deltaDist = glm::abs(glm::vec3(1.0f) / direction);

    int stepX = (direction.x < 0) ? -1 : 1;
    int stepY = (direction.y < 0) ? -1 : 1;
    int stepZ = (direction.z < 0) ? -1 : 1;

    float sideDistX = (direction.x < 0) ? (origin.x - current.x) * deltaDist.x : (current.x + 1.0f - origin.x) * deltaDist.x;
    float sideDistY = (direction.y < 0) ? (origin.y - current.y) * deltaDist.y : (current.y + 1.0f - origin.y) * deltaDist.y;
    float sideDistZ = (direction.z < 0) ? (origin.z - current.z) * deltaDist.z : (current.z + 1.0f - origin.z) * deltaDist.z;

    glm::ivec3 previous = current;
    float distance = 0.0f;

    while(distance < maxDistance)
    {
        int chunkX = (int)std::floor(current.x / (float)CHUNK_SIZE_X);
        int chunkZ = (int)std::floor(current.z / (float)CHUNK_SIZE_Z);

        int localX = current.x - chunkX * CHUNK_SIZE_X;
        int localZ = current.z - chunkZ * CHUNK_SIZE_Z;

        Chunk* chunk = Game::getInstance()->getWorld()->getChunkAt(glm::ivec2(chunkX, chunkZ));
        if(!chunk)
            return false;

        Block block = chunk->getBlock(localX, current.y, localZ);
        if(block.getType() != Block::Type::Air)
        {
            outHit->block = &block;
            outHit->position = origin + direction * distance;
            outHit->previousBlockPosition = glm::vec3(previous);
            outHit->distance = distance;
            outHit->chunk = chunk;
            return true;
        }

        if(sideDistX < sideDistY)
        {
            if(sideDistX < sideDistZ)
            {
                current.x += stepX;
                distance = sideDistX;
                sideDistX += deltaDist.x;
            }
            else
            {
                current.z += stepZ;
                distance = sideDistZ;
                sideDistZ += deltaDist.z;
            }
        }
        else
        {
            if(sideDistY < sideDistZ)
            {
                current.y += stepY;
                distance = sideDistY;
                sideDistY += deltaDist.y;
            }
            else
            {
                current.z += stepZ;
                distance = sideDistZ;
                sideDistZ += deltaDist.z;
            }
        }

        previous = current;
    }

    outHit->distance = maxDistance;

    return false;
}