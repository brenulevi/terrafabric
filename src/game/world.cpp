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
    glm::ivec2 chunkPos(globalPosition.x / CHUNK_SIZE_X, globalPosition.z / CHUNK_SIZE_Z);
    Chunk* chunk = getChunkAt(chunkPos);
    if (chunk)
    {
        int localX = globalPosition.x % CHUNK_SIZE_X;
        int localY = globalPosition.y;
        int localZ = globalPosition.z % CHUNK_SIZE_Z;

        if (localX < 0) localX += CHUNK_SIZE_X;
        if (localZ < 0) localZ += CHUNK_SIZE_Z;

        return chunk->getBlock(localX, localY, localZ);
    }
    return nullptr;
}
