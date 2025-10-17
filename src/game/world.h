#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <queue>
#include <unordered_set>

#include "chunk.h"

#define INITIAL_WORLD_RADIUS 4
#define RENDER_DISTANCE 16
#define CHUNKS_TO_GENERATE_PER_FRAME 2

template<> struct std::hash<glm::ivec2>
{
    std::size_t operator()(const glm::ivec2& v) const
    {
        std::size_t h1 = std::hash<int>()(v.x);
        std::size_t h2 = std::hash<int>()(v.y);
        return h1 ^ (h2 << 1); // Combine hashes
    }
};

class World
{
public:
    World();
    ~World();

    void generateInitialChunks();
    void update();

    void breakBlockAt(const glm::vec3& globalPosition);

    Chunk* getChunkAt(const glm::vec3& globalPosition);
    Chunk* getChunkAt(const glm::ivec2& chunkPosition);

    Block* getBlockAt(const glm::vec3& globalPosition);

    inline std::unordered_map<glm::ivec2, Chunk*>& getLoadedChunks() { return _loadedChunks; }

private:
    std::unordered_map<glm::ivec2, Chunk*> _loadedChunks;
    std::queue<glm::ivec2> _chunksToGenerateMesh;
};