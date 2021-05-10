#include "Game.h"

Game::Game()
    :
    window(sf::VideoMode(screenWidth, screenHeight), "Snake"),
    board(sf::Vector2f(50.f, 50.0f), sf::Color::Blue, 5)
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
    board.RenderBorder(window);
    board.RenderCell(window, sf::Vector2i(2, 3), sf::Color::Red);
    board.RenderCell(window, sf::Vector2i(2, 4), sf::Color::Red);
    board.RenderCell(window, sf::Vector2i(2, 5), sf::Color::Red);
    //
    window.display();
}

bool Game::IsRunning() const
{
    return running;
}
