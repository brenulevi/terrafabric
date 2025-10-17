#include "world.h"

#include "core/game.h"

World::World()
{
}

World::~World()
{
    for (auto& pair : _loadedChunks)
    {
        delete pair.second;
    }
}

void World::generateInitialChunks()
{
    for (int x = -INITIAL_WORLD_RADIUS; x <= INITIAL_WORLD_RADIUS; ++x)
    {
        for (int z = -INITIAL_WORLD_RADIUS; z <= INITIAL_WORLD_RADIUS; ++z)
        {
            glm::ivec2 chunkPos(x, z);
            Chunk* chunk = new Chunk(chunkPos);
            _loadedChunks[chunkPos] = chunk;
        }
    }

    for(auto& pair : _loadedChunks)
    {
        pair.second->generateMesh();
    }
}

void World::update()
{
    std::unordered_set<glm::ivec2> chunksToKeep;

    glm::vec3 playerPos = Game::getInstance()->getPlayer()->getTransform().position;
    
    glm::ivec2 playerChunkPos(
        std::floor(playerPos.x / CHUNK_SIZE_X),
        std::floor(playerPos.z / CHUNK_SIZE_Z)
    );

    for(int x = -RENDER_DISTANCE; x < RENDER_DISTANCE; x++)
    {
        for(int z = -RENDER_DISTANCE; z < RENDER_DISTANCE; z++)
        {
            if(x * x + z * z > RENDER_DISTANCE * RENDER_DISTANCE)
                continue;

            glm::ivec2 chunkPos = playerChunkPos + glm::ivec2(x, z);
            chunksToKeep.insert(chunkPos);

            if(_loadedChunks.find(chunkPos) == _loadedChunks.end())
            {
                _loadedChunks[chunkPos] = new Chunk(chunkPos);
                _chunksToGenerateMesh.push(chunkPos);
            }
        }
    }

    for(auto it = _loadedChunks.begin(); it != _loadedChunks.end(); )
    {
        if(chunksToKeep.find(it->first) == chunksToKeep.end())
        {
            delete it->second;
            it = _loadedChunks.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for(int i = 0; i < CHUNKS_TO_GENERATE_PER_FRAME && !_chunksToGenerateMesh.empty(); ++i)
    {
        glm::ivec2 chunkPos = _chunksToGenerateMesh.front();
        _chunksToGenerateMesh.pop();

        Chunk* chunk = getChunkAt(chunkPos);
        if (chunk)
        {
            chunk->generateMesh();
        }
    }
}

void World::breakBlockAt(const glm::vec3 &globalPosition)
{
    glm::ivec3 globalPos(
        std::floor(globalPosition.x),
        std::floor(globalPosition.y),
        std::floor(globalPosition.z)
    );

    Chunk* chunk = getChunkAt(globalPosition);
    if (chunk)
    {
        glm::ivec2 chunkPos = chunk->getChunkPosition();

        int localX = globalPos.x - chunkPos.x * CHUNK_SIZE_X;
        int localZ = globalPos.z - chunkPos.y * CHUNK_SIZE_Z;

        Block* block = chunk->getBlock(localX, globalPos.y, localZ);
        if (!block)
            return;

        block->type = Block::Type::Air;
        _chunksToGenerateMesh.push(chunkPos);

        // Also update neighboring chunks if the broken block is at the edge
        if (localX == 0)
            _chunksToGenerateMesh.push(glm::ivec2(chunkPos.x - 1, chunkPos.y));
        else if (localX == CHUNK_SIZE_X - 1)
            _chunksToGenerateMesh.push(glm::ivec2(chunkPos.x + 1, chunkPos.y));

        if (localZ == 0)
            _chunksToGenerateMesh.push(glm::ivec2(chunkPos.x, chunkPos.y - 1));
        else if (localZ == CHUNK_SIZE_Z - 1)
            _chunksToGenerateMesh.push(glm::ivec2(chunkPos.x, chunkPos.y + 1));
    }
}

Chunk *World::getChunkAt(const glm::vec3 &globalPosition)
{
    glm::ivec2 chunkPos (
        std::floor(globalPosition.x) / CHUNK_SIZE_X,
        std::floor(globalPosition.z) / CHUNK_SIZE_Z
    );

    auto it = _loadedChunks.find(chunkPos);
    if (it != _loadedChunks.end())
        return it->second;

    return nullptr;
}

Chunk *World::getChunkAt(const glm::ivec2 &chunkPosition)
{
    auto it = _loadedChunks.find(chunkPosition);
    if (it != _loadedChunks.end())
        return it->second;

    return nullptr;
}

Block* World::getBlockAt(const glm::vec3 &globalPosition)
{
    glm::ivec3 globalPos(
        std::floor(globalPosition.x),
        std::floor(globalPosition.y),
        std::floor(globalPosition.z)
    );

    Chunk* chunk = getChunkAt(globalPosition);
    if (chunk)
    {
        // floor modulus to get local block position
        int localX = globalPos.x >= 0 ? globalPos.x % CHUNK_SIZE_X : (CHUNK_SIZE_X + (globalPos.x % CHUNK_SIZE_X)) % CHUNK_SIZE_X;
        int localY = globalPos.y;
        int localZ = globalPos.z >= 0 ? globalPos.z % CHUNK_SIZE_Z : (CHUNK_SIZE_Z + (globalPos.z % CHUNK_SIZE_Z)) % CHUNK_SIZE_Z;

        return chunk->getBlock(localX, localY, localZ);
    }

    return nullptr;
}
