#include "chunk.h"

Chunk::Chunk(glm::ivec2 position)
    : _chunkPosition(position)
{
    _worldPosition = glm::vec3(position.x * CHUNK_SIZE_X, 0.0f, position.y * CHUNK_SIZE_Z);

    // Initialize all blocks to Air
    for(int x = 0; x < CHUNK_SIZE_X; ++x)
    {
        for(int y = 0; y < CHUNK_SIZE_Y; ++y)
        {
            for(int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                if(y < 64)
                    _blocks[x][y][z] = Block(Block::Type::Dirt);
                else if(y == 64)
                    _blocks[x][y][z] = Block(Block::Type::Grass);
                else
                    _blocks[x][y][z] = Block(Block::Type::Air);
            }
        }
    }

    VertexBufferLayout layout;
    layout.push<float>(3); // Position
    _mesh = new Mesh(layout);
}

Chunk::~Chunk()
{
    delete _mesh;
}

void Chunk::generateMesh()
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    
    for(int x = 0; x < CHUNK_SIZE_X; ++x)
    {
        for(int y = 0; y < CHUNK_SIZE_Y; ++y)
        {
            for(int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                Block& block = _blocks[x][y][z];
                if(block.getType() == Block::Type::Air)
                    continue;

                bool facesVisible[6];
                facesVisible[0] = verifyFaceVisibility(x, y + 1, z); // Top
                facesVisible[1] = verifyFaceVisibility(x, y - 1, z); // Bottom
                facesVisible[2] = verifyFaceVisibility(x - 1, y, z); // Left
                facesVisible[3] = verifyFaceVisibility(x + 1, y, z); // Right
                facesVisible[4] = verifyFaceVisibility(x, y, z - 1); // Front
                facesVisible[5] = verifyFaceVisibility(x, y, z + 1); // Back

                for(int i = 0; i < 6; i++)
                    if(facesVisible[i])
                        updateMeshData(vertices, indices, x, y, z, i);
            }
        }
    }

    _mesh->vertexBuffer.setData(vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    _mesh->indexBuffer.setData(indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

Block &Chunk::getBlock(int x, int y, int z)
{
    if(x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z)
        throw std::out_of_range("Block coordinates out of range");
    return _blocks[x][y][z];
}

bool Chunk::verifyFaceVisibility(int x, int y, int z)
{
    return verifyLocalVisibility(x, y, z) && verifyGlobalVisibility(x, y, z);
}

bool Chunk::verifyLocalVisibility(int x, int y, int z)
{
    if(x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z)
        return true;

    return _blocks[x][y][z].getType() == Block::Type::Air;
}

bool Chunk::verifyGlobalVisibility(int x, int y, int z)
{
    return true;
}

void Chunk::updateMeshData(std::vector<float> &vertices, std::vector<unsigned int> &indices, int x, int y, int z, int face)
{
    if(face == 0)   // top
    {
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z);
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z);
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z + 1);
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z + 1);
    }
    else if(face == 1) // bottom
    {
        vertices.push_back(x);     vertices.push_back(y); vertices.push_back(z);
        vertices.push_back(x + 1); vertices.push_back(y); vertices.push_back(z);
        vertices.push_back(x + 1); vertices.push_back(y); vertices.push_back(z + 1);
        vertices.push_back(x);     vertices.push_back(y); vertices.push_back(z + 1);
    }
    else if(face == 2) // left
    {
        vertices.push_back(x);     vertices.push_back(y);     vertices.push_back(z);
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z);
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z + 1);
        vertices.push_back(x);     vertices.push_back(y);     vertices.push_back(z + 1);
    }
    else if(face == 3) // right
    {
        vertices.push_back(x + 1); vertices.push_back(y);     vertices.push_back(z);
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z);
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z + 1);
        vertices.push_back(x + 1); vertices.push_back(y);     vertices.push_back(z + 1);
    }
    else if(face == 4) // front
    {
        vertices.push_back(x);     vertices.push_back(y);     vertices.push_back(z);
        vertices.push_back(x + 1); vertices.push_back(y);     vertices.push_back(z);
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z);
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z);
    }
    else if(face == 5) // back
    {
        vertices.push_back(x);     vertices.push_back(y);     vertices.push_back(z + 1);
        vertices.push_back(x + 1); vertices.push_back(y);     vertices.push_back(z + 1);
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z + 1);
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z + 1);
    }

    unsigned int startIndex = vertices.size() / 3 - 4; // Each vertex has 3 components (x, y, z)
    indices.push_back(startIndex);
    indices.push_back(startIndex + 1);
    indices.push_back(startIndex + 2);
    indices.push_back(startIndex + 2);
    indices.push_back(startIndex + 3);
    indices.push_back(startIndex);
}
