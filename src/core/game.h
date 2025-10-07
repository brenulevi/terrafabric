#pragma once

#include "logging/logger.h"
#include "window.h"
#include "rendering/renderer.h"
#include "game/player.h"
#include "game/world.h"
#include "input.h"

class Game
{
public:
    Game();
    ~Game();

    void run();

    void onClose();
    void onResize(int width, int height);

    inline World* getWorld() { return _world; }
    inline Player* getPlayer() { return _player; }

    inline static Game* getInstance() { return s_instance; }

private:
    bool _isRunning;

    Window* _window;
    Renderer* _renderer;

    World* _world;
    Player* _player;

    static Game* s_instance;
};