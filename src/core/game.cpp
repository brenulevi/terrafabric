#include "game.h"

#include "game/player.h"
#include "game/chunk.h"

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

        ResourceManager::addShader("chunk",
        "assets/shaders/chunk.vert",
        "assets/shaders/chunk.frag");
        Logger::info("Shader 'chunk' loaded");

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

    Player player;
    Chunk chunk(glm::ivec2(1, -4));
    chunk.generateMesh();

    player.setRotation(glm::vec3(0.0f, -90.0f, 0.0f));

    while(_isRunning)
    {
        _window->pollEvents();

        _renderer->clear();

        _renderer->setView(player.getTransform(), player.getCamera());

        _renderer->drawChunk(chunk.getGlobalPosition(), chunk.getMesh());

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
