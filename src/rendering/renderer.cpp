#include "renderer.h"

Renderer::Renderer()
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("Failed to initialize GLAD");

    _matricesUBO = new UniformBuffer(2 * sizeof(glm::mat4), 0); // Binding point 0

    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Renderer::~Renderer()
{
    delete _matricesUBO;
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

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, globalPosition);
    shader->setUniformMat4("model", glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, mesh->indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::setViewport(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void Renderer::onResize(int width, int height)
{
    setViewport(0, 0, width, height);
}
