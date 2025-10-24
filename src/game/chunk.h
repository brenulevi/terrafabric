#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "block.h"
#include "rendering/mesh.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16

class Chunk
{
public:
    Chunk(const glm::vec3& localPosition);

    void generateMesh();

    // That function don't have seg fault handling, need to get block in local chunk coords only
    Block getBlock(int x, int y, int z);
    // That function don't have seg fault handling, need to set block in local chunk coords only
    void setBlock(int x, int y, int z, Block::Type block);

    glm::vec3 getWorldPosition();
    Mesh& getMesh();

private:
    bool checkVisibility(int x, int y, int z) const;
    bool checkLocalVisibility(int x, int y, int z) const;
    bool checkGlobalVisibility(int x, int y, int z) const;
    void addFaceToMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, int x, int y, int z, int faceIndex);

private:
    glm::vec3 _localPosition;
    glm::vec3 _worldPosition;

    std::unique_ptr<Mesh> _mesh;

    Block _blocks[CHUNK_SIZE_X][CHUNK_SIZE_Y][CHUNK_SIZE_Z];
};