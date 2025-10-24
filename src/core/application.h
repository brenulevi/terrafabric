#pragma once

#include <memory>

#include "window.h"
#include "rendering/renderer.h"
#include "assetmanager.h"
#include "input.h"

#include "game/player.h"
#include "game/cube.h"
#include "game/world.h"

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
    std::unique_ptr<AssetManager> _assetManager;
    std::unique_ptr<Input> _input;

    std::unique_ptr<Player> _player;
    std::unique_ptr<Cube> _cube;
    std::unique_ptr<World> _world;

    bool _isRunning;
};