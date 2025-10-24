#include "renderer.h"

Renderer::Renderer()
{
    gladLoadGL();

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    _matricesUBO = std::make_unique<UniformBuffer>(2 * sizeof(glm::mat4), 0);

    AssetManager::get()->loadShader("cube", "assets/shaders/cube.vert", "assets/shaders/cube.frag");
    AssetManager::get()->loadShader("chunk", "assets/shaders/chunk.vert", "assets/shaders/chunk.frag");
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::beginFrame(const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix)
{
    _matricesUBO->setData(0, sizeof(glm::mat4), &viewMatrix);
    _matricesUBO->setData(sizeof(glm::mat4), sizeof(glm::mat4), &projectionMatrix);
}

void Renderer::drawCube(Transform &transform, Mesh &mesh, Texture &texture)
{
    Shader& shader = AssetManager::get()->getShader("cube");
    shader.bind();

    glm::mat4 modelMatrix = transform.getModelMatrix();
    shader.setMat4("uModel", glm::value_ptr(modelMatrix));

    texture.bind(0);
    shader.setInt("uTexture", 0);

    mesh.bind();
    glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);
    mesh.unbind();

    shader.unbind();
}

void Renderer::drawChunk(const glm::vec3 &position, Mesh &mesh)
{
    Shader& shader = AssetManager::get()->getShader("chunk");
    shader.bind();

    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);
    shader.setMat4("uModel", glm::value_ptr(modelMatrix));

    mesh.bind();
    glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);
    mesh.unbind();

    shader.unbind();
}

void Renderer::onResize(int width, int height)
{
    glViewport(0, 0, width, height);
}
