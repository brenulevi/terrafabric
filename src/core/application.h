#pragma once

#include <memory>

#include "window.h"
#include "rendering/renderer.h"

class Application
{
public:
    Application();

    void loop();

private:
    void onClose();
    void onResize(int width, int height);

private:
    std::unique_ptr<Window> _window;
    std::unique_ptr<Renderer> _renderer;

    bool _isRunning;
};