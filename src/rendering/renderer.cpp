#include "renderer.h"

Renderer::Renderer()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    _matricesUBO = new UniformBuffer(2 * sizeof(glm::mat4), 0); // Binding point 0
    _orthoUBO = new UniformBuffer(sizeof(glm::mat4), 1);    // Binding point 1

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _orthoUBO->bind();
    glm::mat4 ortho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
    _orthoUBO->setSubData(0, sizeof(glm::mat4), glm::value_ptr(ortho));
}

Renderer::~Renderer()
{
    delete _matricesUBO;
    delete _orthoUBO;
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setView(Transform& transform, Camera &camera)
{
    glm::mat4 projection = glm::perspective(glm::radians(camera.fov), camera.aspectRatio, camera.nearClip, camera.farClip);
    glm::mat4 view = glm::lookAt(transform.position, transform.position + transform.forward, transform.up);

    // Set the view and projection matrices in the uniform buffer
    _matricesUBO->bind();
    _matricesUBO->setSubData(0, sizeof(glm::mat4), glm::value_ptr(projection));
    _matricesUBO->setSubData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
}

void Renderer::drawChunk(const glm::vec3 &globalPosition, Mesh *mesh)
{
    Shader* shader = ResourceManager::getShader("chunk");
    shader->bind();

    mesh->vertexArray.bind();
    mesh->indexBuffer.bind();

    ResourceManager::getTexture("atlas")->bind(0);
    shader->setUniform1i("uAtlasTexture", 0);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, globalPosition);
    shader->setUniformMat4("model", glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, mesh->indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::drawSprite(const glm::vec2 &position, const glm::vec2 &size, float rotation, Texture *texture)
{
    Shader* shader = ResourceManager::getShader("sprite");
    shader->bind();

    texture->bind(0);
    shader->setUniform1i("uSprite", 0);

    auto quadMesh = ResourceManager::getMesh("quad");
    quadMesh->vertexArray.bind();
    quadMesh->indexBuffer.bind();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));
    shader->setUniformMat4("model", glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, quadMesh->indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::setViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void Renderer::onResize(int width, int height)
{
    setViewport(0, 0, width, height);

    _orthoUBO->bind();
    glm::mat4 ortho = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    _orthoUBO->setSubData(0, sizeof(glm::mat4), glm::value_ptr(ortho));
}
