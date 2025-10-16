#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

#include "chunk.h"

#define WORLD_SIZE 5

struct IVec2Hash
{
    std::size_t operator()(const glm::ivec2& v) const
    {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
    }
};

class World
{
public:
    World();
    ~World();

    void generateWorld();

    Chunk* getChunkAt(const glm::ivec2& chunkPosition);
    Block getBlockAt(const glm::ivec3& globalPosition);

    inline std::unordered_map<glm::ivec2, Chunk*, IVec2Hash>& getAllChunks() { return _chunks; }

private:
    std::unordered_map<glm::ivec2, Chunk*, IVec2Hash> _chunks;
};