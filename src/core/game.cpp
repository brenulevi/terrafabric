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

        Logger::info("Loading resources");

        ResourceManager::addShader("basic",
        "./assets/shaders/basic.vert",
        "./assets/shaders/basic.frag");
        Logger::info("Shader 'basic' loaded");

        ResourceManager::addShader("chunk",
        "./assets/shaders/chunk.vert",
        "./assets/shaders/chunk.frag");
        Logger::info("Shader 'chunk' loaded");

        ResourceManager::addShader("sprite",
        "./assets/shaders/sprite.vert",
        "./assets/shaders/sprite.frag");

        ResourceManager::addTexture("atlas", "./assets/textures/atlas.png");

        ResourceManager::addTexture("crosshair", "./assets/textures/crosshair.png");

        Logger::info("Loading quad mesh");
        float quadVertices[] = {
            // positions    // texCoords
            -0.5f, -0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.0f, 1.0f
        };
        unsigned int quadIndices[] = {
            0, 1, 2,
            2, 3, 0
        };
        VertexBufferLayout quadLayout;
        quadLayout.push<float>(2); // Position
        quadLayout.push<float>(2); // TexCoords
        auto quadMesh = ResourceManager::addMesh("quad", quadLayout);
        quadMesh->vertexBuffer.setData(sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
        quadMesh->indexBuffer.setData(sizeof(quadIndices), quadIndices, GL_STATIC_DRAW);
        Logger::info("Mesh 'quad' loaded");

        Logger::info("Resources loaded");
    }
    catch(const std::exception& e)
    {
        Logger::error(e.what());
        return;
    }

    _world = new World();
    _world->generateWorld();
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
        float deltaTime = glfwGetTime() - totalTime;
        totalTime += deltaTime;

        _window->pollEvents();
        Input::update();

        _player->update(deltaTime);

        if(Input::isKeyPressed(GLFW_KEY_ESCAPE))
            onClose();

        if(Input::isKeyPressed(GLFW_KEY_F11))
            _window->setFullscreen(!_window->isFullscreen());

        if(Input::isKeyPressed(GLFW_KEY_C))
            _renderer->setPolygonMode(GL_LINE);
        if(Input::isKeyPressed(GLFW_KEY_V))
            _renderer->setPolygonMode(GL_FILL);

        _renderer->clear();

        _renderer->setView(_player->getTransform(), _player->getCamera());

        // Render all chunks
        for(auto& pair : _world->getAllChunks())
        {
            Chunk* chunk = pair.second;
            _renderer->drawChunk(chunk->getGlobalPosition(), chunk->getMesh());
        }

        // Render crosshair
        auto crosshairTexture = ResourceManager::getTexture("crosshair");
        float x = (_window->getWidth() - crosshairTexture->getWidth()) / 2.0f;
        float y = (_window->getHeight() - crosshairTexture->getHeight()) / 2.0f;
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
