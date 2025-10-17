#include "world.h"

World::World()
{
}

World::~World()
{
    for (auto& pair : _chunks)
    {
        delete pair.second;
    }
}

void World::generateWorld()
{
    for (int x = -WORLD_SIZE; x <= WORLD_SIZE; ++x)
    {
        for (int z = -WORLD_SIZE; z <= WORLD_SIZE; ++z)
        {
            glm::ivec2 chunkPos(x, z);
            Chunk* chunk = new Chunk(chunkPos);
            _chunks[chunkPos] = chunk;
        }
    }

    for(auto& pair : _chunks)
    {
        pair.second->generateMesh();
    }
}

void World::invalidateChunkAt(const glm::vec3 &chunkGlobalPosition)
{
    glm::ivec2 chunkPos(chunkGlobalPosition.x / CHUNK_SIZE_X, chunkGlobalPosition.z / CHUNK_SIZE_Z);
    Chunk* chunk = getChunkAt(chunkPos);
    if (chunk)
    {
        chunk->generateMesh();
        
        Chunk* neighborsChunks[] = {
            getChunkAt(chunkPos + glm::ivec2(1, 0)),
            getChunkAt(chunkPos + glm::ivec2(-1, 0)),
            getChunkAt(chunkPos + glm::ivec2(0, 1)),
            getChunkAt(chunkPos + glm::ivec2(0, -1))
        };

        for (Chunk* neighbor : neighborsChunks)
        {
            if (neighbor)
                neighbor->generateMesh();
        }
    }
}

Chunk *World::getChunkAt(const glm::ivec2 &chunkPosition)
{
    auto it = _chunks.find(chunkPosition);
    if (it != _chunks.end())
    {
        return it->second;
    }
    return nullptr;
}

Block* World::getBlockAt(const glm::ivec3 &globalPosition)
{
    // floor division to get chunk position
    glm::ivec2 chunkPos(
        globalPosition.x >= 0 ? globalPosition.x / CHUNK_SIZE_X : (globalPosition.x - CHUNK_SIZE_X + 1) / CHUNK_SIZE_X,
        globalPosition.z >= 0 ? globalPosition.z / CHUNK_SIZE_Z : (globalPosition.z - CHUNK_SIZE_Z + 1) / CHUNK_SIZE_Z
    );
    Chunk* chunk = getChunkAt(chunkPos);
    if (chunk)
    {
        // floor modulus to get local block position
        int localX = globalPosition.x >= 0 ? globalPosition.x % CHUNK_SIZE_X : (CHUNK_SIZE_X + (globalPosition.x % CHUNK_SIZE_X)) % CHUNK_SIZE_X;
        int localY = globalPosition.y;
        int localZ = globalPosition.z >= 0 ? globalPosition.z % CHUNK_SIZE_Z : (CHUNK_SIZE_Z + (globalPosition.z % CHUNK_SIZE_Z)) % CHUNK_SIZE_Z;

        return chunk->getBlock(localX, localY, localZ);
    }
    return nullptr;
}
