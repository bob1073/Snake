#include "Game.h"
#include <iostream>

Game::Game()
    :
    window(sf::VideoMode(screenWidth, screenHeight), "Snake"),
    board(window, sf::Vector2f(50.f, 50.0f), sf::Color::Blue, 5),
    snake({2, 2})
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
    dt = dtClock.restart().asSeconds();

    if (!gameOver)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            deltaPos = { 0,-1 };
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            deltaPos = { 0,1 };
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            deltaPos = { -1,0 };
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            deltaPos = { 1,0 };
        }

        snakeMoveTimer += dt;

        if (snakeMoveTimer >= snakeMovePeriod)
        {
            snakeMoveTimer = 0.0f;

            const sf::Vector2i nextPos = snake.GetNextHeadPosition(deltaPos);
            if (!board.IsInsideBoard(nextPos) || snake.IsInTileExceptEnd(nextPos))
            {
                gameOver = true;
            }
            else
            {
                snake.Move(deltaPos);
            }
        }
    }
}

void Game::Render()
{
    window.clear();
    // Render things here
    board.RenderBorder();
    snake.Render(board);
    //
    window.display();
}

bool Game::IsRunning() const
{
    return running;
}
