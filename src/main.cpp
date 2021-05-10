#include "Game.h"

int main()
{
    Game game;

    while (game.IsRunning())
    {
        // Frame start
        game.UpdateEvents();
        game.Update();
        game.Render();
        // Frame end
    }

    return 0;
}