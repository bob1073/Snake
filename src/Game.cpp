#include "Game.h"
#include <iostream>

Game::Game()
    :
    window(sf::VideoMode(screenWidth, screenHeight), "Snake", sf::Style::Titlebar | sf::Style::Close),
    random(std::random_device()()),
    board(window, sf::Vector2f(50.f, 50.0f), sf::Color::Blue, 5),
    snake({2, 2}),
    goal(random, board, snake)
{
    // Init font and texts
    if (!font.loadFromFile("Resources/Fonts/ARCADE.ttf"))
    {
        std::cout << "Error al cargar la fuente, no se pudo abrir el archivo ARCADE.ttf" << std::endl;
    }

    // Starting text
    startText.setFont(font);
    startText.setCharacterSize(60);
    startText.setString("Press Enter to play");
    startText.setPosition(screenWidth / 5.0f, screenHeight / 5.0f);

    // Score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition(screenWidth / 10.0f, screenHeight / 10.0f);

    // Game over text
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(60);
    gameOverText.setString("Game Over");
    gameOverText.setPosition(screenWidth / 2.0f, screenHeight / 2.0f);
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

    if (!gameStart)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            gameStart = true;
        }
    }
    else
    {
        // Game starts here
        UpdateSnake(dt);
    }
}

void Game::Render()
{
    window.clear();
    /*Render things here*/
    if (gameOver)
    {
        window.draw(gameOverText);
    }
    if (gameStart)
    {
        snake.Render(board);
        goal.Render(board);
        window.draw(scoreText);
    }
    else
    {
        window.draw(startText);
    }
    board.RenderBorder();
    
    /********************/
    window.display();
}

bool Game::IsRunning() const
{
    return running;
}

void Game::UpdateSnake(const float& dt)
{
    if (!gameOver)
    {
        // Input to control the snake
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && deltaPos != sf::Vector2i(0,1))
        {
            deltaPos = { 0,-1 };
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && deltaPos != sf::Vector2i(0, -1))
        {
            deltaPos = { 0,1 };
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && deltaPos != sf::Vector2i(1, 0))
        {
            deltaPos = { -1,0 };
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && deltaPos != sf::Vector2i(-1, 0))
        {
            deltaPos = { 1,0 };
        }


        // Manage discrete movement
        snakeMoveTimer += dt;
        if (snakeMoveTimer >= snakeMovePeriod)
        {
            snakeMoveTimer = 0.0f;

            const sf::Vector2i nextPos = snake.GetNextHeadPosition(deltaPos);
            if (!board.IsInsideBoard(nextPos) || snake.IsInTileExceptEnd(nextPos))
            {
                gameOver = true;
                PlaySound(deathSound, "Resources/Audio/death.wav");
            }
            else
            {
                const bool eating = nextPos == goal.GetPosition();

                if (eating)
                {
                    snake.Grow();
                    if (snakeMovePeriod >= 0.1f)
                    {
                        snakeMovePeriod -= 0.01f;
                    }
                    // (*)
                }

                snake.Move(deltaPos);

                // If we respawn inside de other of (*), is possible that goal respawn left to snake and in that case goal won't be eaten!
                if (eating)
                {
                    goal.Respawn(random, board, snake);
                    AddScore();
                    PlaySound(growSound, "Resources/Audio/grow.wav");
                }
            }
        }
    }
}

void Game::AddScore()
{
    score++;
    scoreText.setString("Score: " + std::to_string(score));
}

void Game::PlaySound(sf::Sound& sound, std::string fileName)
{
    if (!soundBuffer.loadFromFile(fileName))
    {
        std::cout << "Error al cargar archivo " << fileName << std::endl;
    }
    else
    {
        sound.setBuffer(soundBuffer);
        sound.play();
    }
}
