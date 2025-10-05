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

        Input::initialize();

        Logger::info("Loading resources");

        ResourceManager::addShader("basic",
        "./assets/shaders/basic.vert",
        "./assets/shaders/basic.frag");
        Logger::info("Shader 'basic' loaded");

        ResourceManager::addShader("chunk",
        "./assets/shaders/chunk.vert",
        "./assets/shaders/chunk.frag");
        Logger::info("Shader 'chunk' loaded");

        Logger::info("Loading texture atlas");
        ResourceManager::addTexture("atlas", "./assets/textures/atlas.png");
        Logger::info("Texture 'atlas' loaded");

        Logger::info("Loading crosshair texture");
        ResourceManager::addTexture("crosshair", "./assets/textures/crosshair.png");
        Logger::info("Texture 'crosshair' loaded");

        Logger::info("Resources loaded");
    }
    catch(const std::exception& e)
    {
        Logger::error(e.what());
        return;
    }

    _player = new Player();
    
    _isRunning = true;
}

Game::~Game()
{
    delete _player;

    delete _renderer;
    delete _window;

    glfwTerminate();

    Logger::info("Game terminated");
}

void Game::run()
{
    if(_isRunning)
        Logger::info("Starting game loop");

    Chunk chunk(glm::ivec2(1, -4));
    chunk.generateMesh();

    Input::setCursorMode(CursorMode::DISABLED);

    float totalTime = 0.0f;

    while(_isRunning)
    {
        float deltaTime = glfwGetTime() - totalTime;
        totalTime += deltaTime;

        _window->pollEvents();
        Input::update();

        _player->update(deltaTime);

        if(Input::isKeyPressed(GLFW_KEY_ESCAPE))
            onClose();

        if(Input::isKeyPressed(GLFW_KEY_F11))
            _window->setFullscreen(!_window->isFullscreen());

        _renderer->clear();

        _renderer->setView(_player->getTransform(), _player->getCamera());

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
    _player->onResize(width, height);
}
