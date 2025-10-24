#include "world.h"

World* World::_instance = nullptr;

World::World()
{
    if(_instance)
        return;

    _instance = this;

    for (int x = -WORLD_SIZE; x <= WORLD_SIZE; ++x)
    {
        for (int z = -WORLD_SIZE; z <= WORLD_SIZE; ++z)
        {
            glm::ivec3 chunkPosition = glm::ivec3(x, 0, z);
            _chunks[chunkPosition] = std::make_unique<Chunk>(chunkPosition);
        }
    }

    for(auto& pair : _chunks)
    {
        glm::vec3 pos = glm::vec3(pair.first);

        if(_chunks.find(glm::ivec3(pos.x, pos.y - 1, pos.z)) != _chunks.end())
            pair.second->setNorthNeighbor(_chunks[glm::ivec3(pos.x, pos.y - 1, pos.z)].get());
        if(_chunks.find(glm::ivec3(pos.x, pos.y + 1, pos.z)) != _chunks.end())
            pair.second->setSouthNeighbor(_chunks[glm::ivec3(pos.x, pos.y + 1, pos.z)].get());
        if(_chunks.find(glm::ivec3(pos.x + 1, pos.y, pos.z)) != _chunks.end())
            pair.second->setEastNeighbor(_chunks[glm::ivec3(pos.x + 1, pos.y, pos.z)].get());
        if(_chunks.find(glm::ivec3(pos.x - 1, pos.y, pos.z)) != _chunks.end())
            pair.second->setWestNeighbor(_chunks[glm::ivec3(pos.x - 1, pos.y, pos.z)].get());

        pair.second->generateMesh();
    }
}

Chunk* World::getChunkAt(const glm::ivec3 &globalPosition)
{
    glm::ivec3 chunkCoords = glm::ivec3(
        globalPosition.x / CHUNK_SIZE_X,
        globalPosition.y / CHUNK_SIZE_Y,
        globalPosition.z / CHUNK_SIZE_Z
    );

    auto it = _chunks.find(chunkCoords);
    if (it != _chunks.end())
    {
        return it->second.get();
    }

    return nullptr;
}

std::unordered_map<glm::ivec3, std::unique_ptr<Chunk>, IVec3Hash, IVec3Equal> &World::getChunks()
{
    return _chunks;
}

World *World::get()
{
    return _instance;
}
