#pragma once

#include <glm/glm.hpp>
#include <stdexcept>

#include "block.h"
#include "components/mesh.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 256
#define CHUNK_SIZE_Z 16

#define TEXTURE_ATLAS_SIZE 256
#define TEXTURE_SIZE 32

class Chunk
{
public:
    Chunk(glm::ivec2 chunkPosition);
    ~Chunk();

    void generateMesh();

    inline glm::ivec2 getChunkPosition() const { return _chunkPosition; }
    inline glm::vec3 getGlobalPosition() const { return _worldPosition; }
    Block* getBlock(int localX, int localY, int localZ);
    inline Mesh* getMesh() { return _mesh; }

    void setBlock(int x, int y, int z, Block block);

private:
    bool verifyFaceVisibility(int x, int y, int z);
    bool verifyLocalVisibility(int x, int y, int z);
    bool verifyGlobalVisibility(int x, int y, int z);
    void updateMeshData(std::vector<float>& vertices, std::vector<unsigned int>& indices, int x, int y, int z, int face, Block::Type type);
    glm::vec2 getUV(int face, Block::Type type);

private:
    glm::ivec2 _chunkPosition;
    glm::vec3 _worldPosition;

    Block _blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];

    Mesh* _mesh;
};