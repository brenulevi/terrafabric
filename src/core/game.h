#pragma once

#include "logging/logger.h"
#include "window.h"
#include "rendering/renderer.h"
#include "game/player.h"
#include "input.h"

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

    Player* _player;

    static Game* s_instance;
};