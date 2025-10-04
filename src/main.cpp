#include "logging/logger.h"
#include "core/game.h"

int main()
{
    Logger::init();
    Game game;
    game.run();
    return 0;
}