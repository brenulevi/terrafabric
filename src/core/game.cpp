#include "game.h"

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
    }
    catch(const std::exception& e)
    {
        Logger::error(e.what());
        return;
    }

    _world = new World();
    _world->generateInitialChunks();

    _player = new Player();
    _player->setPosition(glm::vec3(0.0f, 20.0f, 0.0f));

    _isRunning = true;
}

Game::~Game()
{
    Logger::info("Shutting down game");

    delete _world;
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

    Input::setCursorMode(CursorMode::DISABLED);

    float totalTime = 0.0f;

    while(_isRunning)
    {
        _window->pollEvents();

        float deltaTime = glfwGetTime() - totalTime;
        totalTime += deltaTime;

        Input::update();

        _world->update();
        _player->update(deltaTime);

        if(Input::isKeyPressed(GLFW_KEY_ESCAPE))
            onClose();

        if(Input::isKeyPressed(GLFW_KEY_F11))
            _window->setFullscreen(!_window->isFullscreen());

        if(Input::isKeyPressed(GLFW_KEY_C))
            _renderer->setPolygonMode(GL_LINE);
        if(Input::isKeyPressed(GLFW_KEY_V))
            _renderer->setPolygonMode(GL_FILL);

        if(Input::isKeyPressed(GLFW_KEY_F))
        {
            bool isDisabled = Input::getCursorMode() == CursorMode::DISABLED;
            Input::setCursorMode(isDisabled ? CursorMode::NORMAL : CursorMode::DISABLED);
        }

        _renderer->clear();

        _renderer->setView(_player->getTransform(), _player->getCamera());

        // Render all chunks
        for(auto& pair : _world->getLoadedChunks())
        {
            Chunk* chunk = pair.second;
            _renderer->drawChunk(chunk->getGlobalPosition(), chunk->getMesh());
        }

        // Render crosshair
        auto crosshairTexture = ResourceManager::getTexture("crosshair");
        float x = (_window->getWidth()) / 2.0f;
        float y = (_window->getHeight()) / 2.0f;
        float sizeX = crosshairTexture->getWidth();
        float sizeY = crosshairTexture->getHeight();

        _renderer->drawSprite(glm::vec2(x, y), glm::vec2(sizeX, sizeY) * 2.0f, 0.0f, crosshairTexture);

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
