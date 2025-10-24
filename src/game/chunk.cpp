#include "chunk.h"

#include "world.h"

Chunk::Chunk(const glm::vec3 &localPosition)
    : _localPosition(localPosition)
{
    _worldPosition = localPosition * glm::vec3(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z);

    BufferLayout layout;
    layout.addLayoutElement<float>(3); // Position
    layout.addLayoutElement<float>(2); // TexCoords
    _mesh = std::make_unique<Mesh>(layout);

    for (int x = 0; x < CHUNK_SIZE_X; x++)
    {
        for (int y = 0; y < CHUNK_SIZE_Y; y++)
        {
            for (int z = 0; z < CHUNK_SIZE_Z; z++)
            {
                _blocks[x][y][z].type = Block::Type::STONE;
            }
        }
    }
}

void Chunk::generateMesh()
{
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (int x = 0; x < CHUNK_SIZE_X; x++)
    {
        for (int y = 0; y < CHUNK_SIZE_Y; y++)
        {
            for (int z = 0; z < CHUNK_SIZE_Z; z++)
            {
                if (_blocks[x][y][z].type == Block::Type::AIR)
                    continue;

                bool isFaceVisible[6] = {false};
                isFaceVisible[0] = checkVisibility(x, y + 1, z); // Top
                isFaceVisible[1] = checkVisibility(x, y - 1, z); // Bottom
                isFaceVisible[2] = checkVisibility(x - 1, y, z); // Left
                isFaceVisible[3] = checkVisibility(x + 1, y, z); // Right
                isFaceVisible[4] = checkVisibility(x, y, z - 1); // Front
                isFaceVisible[5] = checkVisibility(x, y, z + 1); // Back

                for (int i = 0; i < 6; i++)
                    if (isFaceVisible[i])
                        addFaceToMesh(vertices, indices, x, y, z, i);
            }
        }
    }

    _mesh->setVertices(vertices.data(), static_cast<unsigned int>(vertices.size() * sizeof(float)));
    _mesh->setIndices(indices.data(), static_cast<unsigned int>(indices.size() * sizeof(unsigned int)));
}

Block Chunk::getBlock(int x, int y, int z)
{
    return _blocks[x][y][z];
}

void Chunk::setBlock(int x, int y, int z, Block::Type block)
{
    _blocks[x][y][z].type = block;
}

glm::vec3 Chunk::getWorldPosition()
{
    return _worldPosition;
}

Mesh &Chunk::getMesh()
{
    return *_mesh;
}

bool Chunk::checkVisibility(int x, int y, int z) const
{
    return checkLocalVisibility(x, y, z) && checkGlobalVisibility(x, y, z);
}

bool Chunk::checkLocalVisibility(int x, int y, int z) const
{
    if (x < 0 || x >= CHUNK_SIZE_X ||
        y < 0 || y >= CHUNK_SIZE_Y ||
        z < 0 || z >= CHUNK_SIZE_Z)
    {
        return true; // Out of bounds, consider it visible
    }

    return _blocks[x][y][z].type == Block::Type::AIR;
}

bool Chunk::checkGlobalVisibility(int x, int y, int z) const
{
    if(x > 0 && x < CHUNK_SIZE_X - 1 &&
       y > 0 && y < CHUNK_SIZE_Y - 1 &&
       z > 0 && z < CHUNK_SIZE_Z - 1)
    {
        return true; // Inside the chunk, no need to check global visibility
    }
}

void Chunk::addFaceToMesh(std::vector<float> &vertices, std::vector<unsigned int> &indices, int x, int y, int z, int faceIndex)
{
    if (faceIndex == 0) // Top
    {
        vertices.insert(vertices.end(), {x + 0.0f, y + 1.0f, -(z + 0.0f), 0.0f, 0.0f,
                                         x + 1.0f, y + 1.0f, -(z + 0.0f), 1.0f, 0.0f,
                                         x + 1.0f, y + 1.0f, -(z + 1.0f), 1.0f, 1.0f,
                                         x + 0.0f, y + 1.0f, -(z + 1.0f), 0.0f, 1.0f});
    }
    else if (faceIndex == 1) // Bottom
    {
        vertices.insert(vertices.end(), {x + 0.0f, y + 0.0f, -(z + 0.0f), 0.0f, 0.0f,
                                         x + 1.0f, y + 0.0f, -(z + 0.0f), 1.0f, 0.0f,
                                         x + 1.0f, y + 0.0f, -(z + 1.0f), 1.0f, 1.0f,
                                         x + 0.0f, y + 0.0f, -(z + 1.0f), 0.0f, 1.0f});
    }
    else if (faceIndex == 2) // Left
    {
        vertices.insert(vertices.end(), {x + 0.0f, y + 0.0f, -(z + 0.0f), 0.0f, 0.0f,
                                         x + 0.0f, y + 1.0f, -(z + 0.0f), 1.0f, 0.0f,
                                         x + 0.0f, y + 1.0f, -(z + 1.0f), 1.0f, 1.0f,
                                         x + 0.0f, y + 0.0f, -(z + 1.0f), 0.0f, 1.0f});
    }
    else if (faceIndex == 3) // Right
    {
        vertices.insert(vertices.end(), {x + 1.0f, y + 0.0f, -(z + 0.0f), 0.0f, 0.0f,
                                         x + 1.0f, y + 1.0f, -(z + 0.0f), 1.0f, 0.0f,
                                         x + 1.0f, y + 1.0f, -(z + 1.0f), 1.0f, 1.0f,
                                         x + 1.0f, y + 0.0f, -(z + 1.0f), 0.0f, 1.0f});
    }
    else if (faceIndex == 4) // Front
    {
        vertices.insert(vertices.end(), {x + 0.0f, y + 0.0f, -(z + 0.0f), 0.0f, 0.0f,
                                         x + 1.0f, y + 0.0f, -(z + 0.0f), 1.0f, 0.0f,
                                         x + 1.0f, y + 1.0f, -(z + 0.0f), 1.0f, 1.0f,
                                         x + 0.0f, y + 1.0f, -(z + 0.0f), 0.0f, 1.0f});
    }
    else if (faceIndex == 5) // Back
    {
        vertices.insert(vertices.end(), {
                                            x + 0.0f,
                                            y + 0.0f,
                                            -(z + 1.0f),
                                            0.0f,
                                            0.0f,
                                            x + 1.0f,
                                            y + 0.0f,
                                            -(z + 1.0f),
                                            1.0f,
                                            0.0f,
                                            x + 1.0f,
                                            y + 1.0f,
                                            -(z + 1.0f),
                                            1.0f,
                                            1.0f,
                                            x + 0.0f,
                                            y + 1.0f,
                                            -(z + 1.0f),
                                            0.0f,
                                            1.0f,
                                        });
    }

    unsigned int startIndex = static_cast<unsigned int>(vertices.size() / 5) - 4;
    ;
    indices.insert(indices.end(), {startIndex, startIndex + 1, startIndex + 2,
                                   startIndex, startIndex + 2, startIndex + 3});
}
