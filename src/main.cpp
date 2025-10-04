#include "logger.h"
#include "game.h"

int main()
{
    Logger::init();
    Game game;
    game.run();
    return 0;
}