#pragma once

#include <glm/glm.hpp>
#include <stdexcept>

#include "block.h"
#include "rendering/mesh.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 256
#define CHUNK_SIZE_Z 16

class Chunk
{
public:
    Chunk(glm::ivec2 chunkPosition);
    ~Chunk();

    void generateMesh();

    inline glm::ivec2 getChunkPosition() const { return _chunkPosition; }
    inline glm::vec3 getGlobalPosition() const { return _worldPosition; }
    Block& getBlock(int x, int y, int z);
    inline Mesh* getMesh() { return _mesh; }

private:
    bool verifyFaceVisibility(int x, int y, int z);
    bool verifyLocalVisibility(int x, int y, int z);
    bool verifyGlobalVisibility(int x, int y, int z);
    void updateMeshData(std::vector<float>& vertices, std::vector<unsigned int>& indices, int x, int y, int z, int face);

private:
    glm::ivec2 _chunkPosition;
    glm::vec3 _worldPosition;

    Block _blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];

    Mesh* _mesh;
};