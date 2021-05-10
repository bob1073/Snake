#include "Game.h"

Game::Game()
	: window(sf::VideoMode(screenWidth, screenHeight), "SFML Game Title")
{
}

Game::~Game()
{
}

void Game::UpdateEvents()
{
    while (window.pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            running = false;
    }
}

void Game::Update()
{

}

void Game::Render()
{
    window.clear();
    // Render things here

    //
    window.display();
}

bool Game::IsRunning() const
{
    return running;
}
