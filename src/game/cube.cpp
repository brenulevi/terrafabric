#include "cube.h"

Cube::Cube()
    : _texture(AssetManager::get()->loadTexture("cube", "assets/textures/cube_texture.png"))
{
    // Define the layout for the cube mesh (position only for simplicity)
    BufferLayout layout;
    layout.addLayoutElement<float>(3); // position
    layout.addLayoutElement<float>(2); // texture coordinates

    _mesh = std::make_unique<Mesh>(layout);

    // Define cube vertices and indices
    float vertices[] = {
        // positions        // tex coords
        // Back face
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 0
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // 1
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // 2
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // 3

        // Front face
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // 4
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // 5
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // 6
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // 7

        // Left face
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 8
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f,  // 9
        -0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // 10
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,  // 11

        // Right face
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 12
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f,  // 13
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // 14
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f,  // 15

        // Bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // 16
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // 17
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f,   // 18
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f,  // 19

        // Top face
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, // 20
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f,  // 21
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // 22
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f   // 23
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,       // Back
        4, 5, 6, 6, 7, 4,       // Front
        8, 9, 10, 10, 11, 8,    // Left
        12, 13, 14, 14, 15, 12, // Right
        16, 17, 18, 18, 19, 16, // Bottom
        20, 21, 22, 22, 23, 20  // Top
    };

    _mesh->setVertices(vertices, sizeof(vertices));
    _mesh->setIndices(indices, sizeof(indices));

    _transform.position = glm::vec3(0.0f, 0.0f, -5.0f);
}

void Cube::update()
{
    _transform.updateVectors();

    _transform.rotation.y += 1.0f;
    _transform.rotation.x += 0.8f;
}

Transform &Cube::getTransform()
{
    return _transform;
}

Mesh &Cube::getMesh()
{
    return *_mesh;
}

Texture &Cube::getTexture()
{
    return _texture;
}
