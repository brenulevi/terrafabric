#pragma once

#include "logger.h"
#include "window.h"
#include "renderer.h"

class Game
{
public:
    Game();
    ~Game();

    void run();

    void onClose();
    void onResize(int width, int height);

    inline static Game* getInstance() { return s_instance; }

private:
    bool _isRunning;

    Window* _window;
    Renderer* _renderer;

    static Game* s_instance;
};