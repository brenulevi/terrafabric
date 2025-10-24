#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

#include "chunk.h"

struct IVec3Hash {
    std::size_t operator()(const glm::ivec3& v) const noexcept {
        // Combina os três inteiros em um hash
        std::size_t h1 = std::hash<int>{}(v.x);
        std::size_t h2 = std::hash<int>{}(v.y);
        std::size_t h3 = std::hash<int>{}(v.z);

        // Combinação padrão
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
};

struct IVec3Equal {
    bool operator()(const glm::ivec3& a, const glm::ivec3& b) const noexcept {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};

#define WORLD_SIZE 5

class World
{
public:
    World();

    Chunk* getChunkAt(const glm::ivec3& globalPosition);

    std::unordered_map<glm::ivec3, std::unique_ptr<Chunk>, IVec3Hash, IVec3Equal>& getChunks();

    static World* get();

private:
    std::unordered_map<glm::ivec3, std::unique_ptr<Chunk>, IVec3Hash, IVec3Equal> _chunks;

    static World* _instance;
};