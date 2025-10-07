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

void World::breakBlock(Chunk *chunk, const glm::ivec3 &localPosition)
{
    if(!chunk)
        return;

    chunk->setBlock(localPosition.x, localPosition.y, localPosition.z, Block(Block::Type::Air));
    chunk->generateMesh();

    if(localPosition.x == 0)
    {
        Chunk* neighbor = getChunkAt(chunk->getChunkPosition() + glm::ivec2(-1, 0));
        if(neighbor)
            neighbor->generateMesh();
    }
    else if(localPosition.x == CHUNK_SIZE_X - 1)
    {
        Chunk* neighbor = getChunkAt(chunk->getChunkPosition() + glm::ivec2(1, 0));
        if(neighbor)
            neighbor->generateMesh();
    }

    if(localPosition.z == 0)
    {
        Chunk* neighbor = getChunkAt(chunk->getChunkPosition() + glm::ivec2(0, -1));
        if(neighbor)
            neighbor->generateMesh();
    }
    else if(localPosition.z == CHUNK_SIZE_Z - 1)
    {
        Chunk* neighbor = getChunkAt(chunk->getChunkPosition() + glm::ivec2(0, 1));
        if(neighbor)
            neighbor->generateMesh();
    }
}

void World::placeBlock(Chunk *chunk, const glm::ivec3 &localPosition, Block block)
{
    if(!chunk)
        return;

    chunk->setBlock(localPosition.x, localPosition.y, localPosition.z, block);
    chunk->generateMesh();

    if(localPosition.x == 0)
    {
        Chunk* neighbor = getChunkAt(chunk->getChunkPosition() + glm::ivec2(-1, 0));
        if(neighbor)
            neighbor->generateMesh();
    }
    else if(localPosition.x == CHUNK_SIZE_X - 1)
    {
        Chunk* neighbor = getChunkAt(chunk->getChunkPosition() + glm::ivec2(1, 0));
        if(neighbor)
            neighbor->generateMesh();
    }

    if(localPosition.z == 0)
    {
        Chunk* neighbor = getChunkAt(chunk->getChunkPosition() + glm::ivec2(0, -1));
        if(neighbor)
            neighbor->generateMesh();
    }
    else if(localPosition.z == CHUNK_SIZE_Z - 1)
    {
        Chunk* neighbor = getChunkAt(chunk->getChunkPosition() + glm::ivec2(0, 1));
        if(neighbor)
            neighbor->generateMesh();
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