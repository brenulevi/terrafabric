#include "game.h"

#include "vertexbuffer.h"
#include "vertexarray.h"

Game* Game::s_instance = nullptr;

Game::Game()
    : _window(nullptr), _renderer(nullptr), _isRunning(false)
{
    if(s_instance)
    {
        Logger::error("Game instance already exists!");
        return;
    }

    s_instance = this;

    Logger::info("Initializing GLFW");
    if(!glfwInit())
    {
        Logger::error("Failed to initialize GLFW");
        return;
    }
    Logger::info("GLFW initialized");        

    try
    {
        Logger::info("Creating window");
        _window = new Window(800, 600, "TerraFabric");
        _window->setOnCloseCallback(std::bind(&Game::onClose, this));
        _window->setOnResizeCallback(std::bind(&Game::onResize, this, std::placeholders::_1, std::placeholders::_2));
        Logger::info("Window created");

        Logger::info("Creating renderer");
        _renderer = new Renderer();
        _renderer->setViewport(0, 0, 800, 600);
        Logger::info("Renderer created");

        Logger::info("Loading resources");

        ResourceManager::addShader("basic",
        "assets/shaders/basic.vert",
        "assets/shaders/basic.frag");
        Logger::info("Shader 'basic' loaded");

        Logger::info("Resources loaded");
    }
    catch(const std::exception& e)
    {
        Logger::error(e.what());
        return;
    }
    
    _isRunning = true;
}

Game::~Game()
{
    delete _renderer;
    delete _window;

    glfwTerminate();

    Logger::info("Game terminated");
}

void Game::run()
{
    if(_isRunning)
        Logger::info("Starting game loop");

    auto shader = ResourceManager::getShader("basic");
    VertexBuffer vb;
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(2); // texCoord
    layout.push<float>(3); // normal
    VertexArray va;
    va.addBuffer(vb, layout);

    float vertices[] = {
        // positions        // texCoords  // normals
         0.0f,  0.5f, 0.0f,  0.5f, 1.0f,   0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,   0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   0.0f, 0.0f, 1.0f
    };

    while(_isRunning)
    {
        _window->pollEvents();

        _renderer->clear();

        shader->bind();
        va.bind();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        _window->swapBuffers();
    }
}

void Game::onClose()
{
    _isRunning = false;
    Logger::info("Game closing...");
}

void Game::onResize(int width, int height)
{
    Logger::info("Window resized to {}x{}", width, height);
    _renderer->onResize(width, height);
}
