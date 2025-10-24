#include "application.h"

Application::Application()
    : _isRunning(true)
{
    _window = std::make_unique<Window>(800, 600, "Terrafabric");
    _window->setCloseCallback(std::bind(&Application::onClose, this));
    _window->setResizeCallback(std::bind(&Application::onResize, this, std::placeholders::_1, std::placeholders::_2));

    _assetManager = std::make_unique<AssetManager>();
    _renderer = std::make_unique<Renderer>();
    _input = std::make_unique<Input>();

    _player = std::make_unique<Player>();
    _cube = std::make_unique<Cube>();
    _world = std::make_unique<World>();
}

void Application::loop()
{
    while(_isRunning)
    {
        _window->update();
        _input->update(_window->getPtr());

        if(Input::get()->isKeyPressed(GLFW_KEY_ESCAPE))
            onClose();

        _player->update();
        _cube->update();

        _renderer->clear();

        _renderer->beginFrame(_player->getViewMatrix(), _player->getCamera().getProjectionMatrix());
        _renderer->drawCube(_cube->getTransform(), _cube->getMesh(), _cube->getTexture());
    
        for(auto& pair : _world->getChunks())
        {
            Chunk& chunk = *pair.second;
            _renderer->drawChunk(chunk.getWorldPosition(), chunk.getMesh());
        }

        _window->present();
    }
}

void Application::onClose()
{
    _isRunning = false;
}

void Application::onResize(int width, int height)
{
    _renderer->onResize(width, height);
}
