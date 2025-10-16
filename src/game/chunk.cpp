#include "chunk.h"

#include "core/game.h"

Chunk::Chunk(glm::ivec2 position)
    : _chunkPosition(position)
{
    _worldPosition = glm::vec3(position.x * CHUNK_SIZE_X, 0.0f, position.y * CHUNK_SIZE_Z);

    for(int x = 0; x < CHUNK_SIZE_X; ++x)
    {
        for(int y = 0; y < CHUNK_SIZE_Y; ++y)
        {
            for(int z = 0; z < CHUNK_SIZE_Z; ++z)
            {
                Block block;
                block.type = Block::Type::Grass;
                _blocks[x][y][z] = block;
            }
        }
    }

    VertexBufferLayout layout;
    layout.push<float>(3); // Position
    layout.push<float>(2); // UVs
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
                if(block.type == Block::Type::Air)
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
                        updateMeshData(vertices, indices, x, y, z, i, block.type);
            }
        }
    }

    _mesh->vertexBuffer.setData(vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    _mesh->indexBuffer.setData(indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

Block* Chunk::getBlock(int x, int y, int z)
{
    if(x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z)
        return nullptr;
    return &_blocks[x][y][z];
}

void Chunk::setBlock(int x, int y, int z, Block block)
{
    if(x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z)
        throw std::out_of_range("Block position out of range in chunk");

    _blocks[x][y][z] = block;
}

bool Chunk::verifyFaceVisibility(int x, int y, int z)
{
    return verifyLocalVisibility(x, y, z) && verifyGlobalVisibility(x, y, z);
}

bool Chunk::verifyLocalVisibility(int x, int y, int z)
{
    if(x < 0 || x >= CHUNK_SIZE_X || y < 0 || y >= CHUNK_SIZE_Y || z < 0 || z >= CHUNK_SIZE_Z)
        return true;

    return _blocks[x][y][z].type == Block::Type::Air;
}

bool Chunk::verifyGlobalVisibility(int x, int y, int z)
{
   if(x > 0 && x < CHUNK_SIZE_X - 1 && z > 0 && z < CHUNK_SIZE_Z - 1)
        return true;

    Chunk* neighbor = Game::getInstance()->getWorld()->getChunkAt(
        glm::ivec2(
            _chunkPosition.x + (x < 0 ? -1 : (x >= CHUNK_SIZE_X ? 1 : 0)),
            _chunkPosition.y + (z < 0 ? -1 : (z >= CHUNK_SIZE_Z ? 1 : 0))
        )
    );

    if(!neighbor)
        return true;

    Block* neighborBlock = neighbor->getBlock(
        (x < 0 ? CHUNK_SIZE_X - 1 : (x >= CHUNK_SIZE_X ? 0 : x)),
        y,
        (z < 0 ? CHUNK_SIZE_Z - 1 : (z >= CHUNK_SIZE_Z ? 0 : z))
    );

    if(!neighborBlock)
        return true;

    return neighborBlock->type == Block::Type::Air;
}

void Chunk::updateMeshData(std::vector<float> &vertices, std::vector<unsigned int> &indices, int x, int y, int z, int face, Block::Type type)
{
    glm::vec2 leftUV = getUV(face, type);
    glm::vec2 rightUV;
    rightUV.x = leftUV.x + (TEXTURE_SIZE / static_cast<float>(TEXTURE_ATLAS_SIZE));
    rightUV.y = leftUV.y + (TEXTURE_SIZE / static_cast<float>(TEXTURE_ATLAS_SIZE));

    if(face == 0)   // top
    {
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z);        vertices.push_back(leftUV.x);  vertices.push_back(leftUV.y);    // Bottom-left
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z);        vertices.push_back(rightUV.x); vertices.push_back(leftUV.y);    // Bottom-right
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z + 1);    vertices.push_back(rightUV.x); vertices.push_back(rightUV.y);   // Top-right
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z + 1);    vertices.push_back(leftUV.x);  vertices.push_back(rightUV.y);   // Top-left
    }
    else if(face == 1) // bottom
    {
        vertices.push_back(x);     vertices.push_back(y); vertices.push_back(z);            vertices.push_back(leftUV.x);  vertices.push_back(leftUV.y);    // Bottom-left
        vertices.push_back(x + 1); vertices.push_back(y); vertices.push_back(z);            vertices.push_back(rightUV.x); vertices.push_back(leftUV.y);    // Bottom-right
        vertices.push_back(x + 1); vertices.push_back(y); vertices.push_back(z + 1);        vertices.push_back(rightUV.x); vertices.push_back(rightUV.y);   // Top-right
        vertices.push_back(x);     vertices.push_back(y); vertices.push_back(z + 1);        vertices.push_back(leftUV.x);  vertices.push_back(rightUV.y);   // Top-left
    }
    else if(face == 2) // left
    {
        vertices.push_back(x);     vertices.push_back(y);     vertices.push_back(z);        vertices.push_back(leftUV.x);  vertices.push_back(leftUV.y);    // Bottom-left
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z);        vertices.push_back(leftUV.x);  vertices.push_back(rightUV.y);   // Top-left
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z + 1);    vertices.push_back(rightUV.x); vertices.push_back(rightUV.y);   // Top-right
        vertices.push_back(x);     vertices.push_back(y);     vertices.push_back(z + 1);    vertices.push_back(rightUV.x); vertices.push_back(leftUV.y);    // Bottom-right
    }
    else if(face == 3) // right
    {
        vertices.push_back(x + 1); vertices.push_back(y);     vertices.push_back(z);        vertices.push_back(leftUV.x);  vertices.push_back(leftUV.y);    // Bottom-left
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z);        vertices.push_back(leftUV.x);  vertices.push_back(rightUV.y);   // Top-left
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z + 1);    vertices.push_back(rightUV.x); vertices.push_back(rightUV.y);   // Top-right
        vertices.push_back(x + 1); vertices.push_back(y);     vertices.push_back(z + 1);    vertices.push_back(rightUV.x); vertices.push_back(leftUV.y);    // Bottom-right
    }
    else if(face == 4) // front
    {
        vertices.push_back(x);     vertices.push_back(y);     vertices.push_back(z);        vertices.push_back(leftUV.x);  vertices.push_back(leftUV.y);    // Bottom-left
        vertices.push_back(x + 1); vertices.push_back(y);     vertices.push_back(z);        vertices.push_back(rightUV.x); vertices.push_back(leftUV.y);    // Bottom-right
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z);        vertices.push_back(rightUV.x); vertices.push_back(rightUV.y);   // Top-right
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z);        vertices.push_back(leftUV.x);  vertices.push_back(rightUV.y);   // Top-left
    }
    else if(face == 5) // back
    {
        vertices.push_back(x);     vertices.push_back(y);     vertices.push_back(z + 1);    vertices.push_back(leftUV.x);  vertices.push_back(leftUV.y);   // Bottom-left
        vertices.push_back(x + 1); vertices.push_back(y);     vertices.push_back(z + 1);    vertices.push_back(rightUV.x); vertices.push_back(leftUV.y);   // Bottom-right
        vertices.push_back(x + 1); vertices.push_back(y + 1); vertices.push_back(z + 1);    vertices.push_back(rightUV.x); vertices.push_back(rightUV.y);  // Top-right
        vertices.push_back(x);     vertices.push_back(y + 1); vertices.push_back(z + 1);    vertices.push_back(leftUV.x);  vertices.push_back(rightUV.y);  // Top-left
    }

    unsigned int startIndex = vertices.size() / 5 - 4; // Each vertex has 3 components (x, y, z)
    indices.push_back(startIndex);      indices.push_back(startIndex + 1);  indices.push_back(startIndex + 2);
    indices.push_back(startIndex + 2);  indices.push_back(startIndex + 3);  indices.push_back(startIndex);
}

glm::vec2 Chunk::getUV(int face, Block::Type type)
{
    int tileX = 0;
    int tileY = 0;

    switch(type)
    {
        case Block::Type::Grass:
            if(face == 0) // Top
            {
                tileX = 0; tileY = 0;
            }
            else if(face == 1) // Bottom
            {
                tileX = 2; tileY = 0;
            }
            else // Sides
            {
                tileX = 1; tileY = 0;
            }
            break;
        case Block::Type::Dirt:
            tileX = 2; tileY = 0;
            break;
        case Block::Type::Stone:
            tileX = 3; tileY = 0;
            break;
        case Block::Type::Bedrock:
            tileX = 4; tileY = 0;
            break;
        default: // Air or unknown type
            tileX = 5; tileY = 0; // Assuming a placeholder texture for air/unknown
            break;
    }

    float u = (tileX * TEXTURE_SIZE) / static_cast<float>(TEXTURE_ATLAS_SIZE);
    float v = (tileY * TEXTURE_SIZE) / static_cast<float>(TEXTURE_ATLAS_SIZE);

    return glm::vec2(u, v);
}
