#include "application.h"

Application::Application()
    : _isRunning(true)
{
    _window = std::make_unique<Window>(800, 600, "Terrafabric");
    _window->setCloseCallback(std::bind(&Application::onClose, this));
    _window->setResizeCallback(std::bind(&Application::onResize, this, std::placeholders::_1, std::placeholders::_2));

    _renderer = std::make_unique<Renderer>();

    _assetManager = std::make_unique<AssetManager>();
}

void Application::loop()
{
    while(_isRunning)
    {
        _window->update();

        _renderer->clear();

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
