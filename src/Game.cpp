#include "Game.h"
#include <iostream>

Game::Game()
    :
    m_window{ 
        sf::VideoMode(s_screenWidth, s_screenHeight), 
        "Snake", sf::Style::Titlebar | sf::Style::Close
    },
    m_event{},
    m_dt{},
    m_random{ std::random_device()() },
    m_board{ m_window, sf::Vector2f(50.f, 50.0f), sf::Color::Blue, 5 },
    m_snake{ {2, 2} },
    m_goal{ m_random, m_board, m_snake }
{
    // Init font and texts
    if (!m_font.loadFromFile("Resources/Fonts/ARCADE.ttf"))
    {
        sf::err() << "Error al cargar la fuente, \n";
        sf::err() << "no se pudo abrir el archivo ARCADE.ttf\n";
    }

    // Starting text
    m_startText.setFont(m_font);
    m_startText.setCharacterSize(60);
    m_startText.setString("Press Enter to play");
    m_startText.setPosition(s_screenWidth / 5.0f, s_screenHeight / 5.0f);

    // Score text
    m_scoreText.setFont(m_font);
    m_scoreText.setCharacterSize(30);
    m_scoreText.setString("Score: " + std::to_string(m_score));
    m_scoreText.setPosition(s_screenWidth / 10.0f, s_screenHeight / 10.0f);

    // Game over text
    m_gameOverText.setFont(m_font);
    m_gameOverText.setCharacterSize(60);
    m_gameOverText.setString("Game Over");
    m_gameOverText.setPosition(s_screenWidth / 2.0f, s_screenHeight / 2.0f);
}

void Game::UpdateEvents()
{
    while (m_window.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed)
            m_running = false;
    }
}

void Game::Update()
{
    m_dt = m_dtClock.restart().asSeconds();

    if (!m_gameStart)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            m_gameStart = true;
        }
    }
    else
    {
        // Game starts here
        UpdateSnake(m_dt);
    }
}

void Game::Render()
{
    m_window.clear();
    /*Render things here*/
    if (m_gameOver)
    {
        m_window.draw(m_gameOverText);
    }
    if (m_gameStart)
    {
        m_snake.Render(m_board);
        m_goal.Render(m_board);
        m_window.draw(m_scoreText);
    }
    else
    {
        m_window.draw(m_startText);
    }
    m_board.RenderBorder();
    
    /********************/
    m_window.display();
}

void Game::UpdateSnake(float dt)
{
    if (!m_gameOver)
    {
        // Input to control the snake
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && 
            m_deltaPos != sf::Vector2i(0,1))
        {
            m_deltaPos = { 0,-1 };
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && 
            m_deltaPos != sf::Vector2i(0, -1))
        {
            m_deltaPos = { 0,1 };
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && 
            m_deltaPos != sf::Vector2i(1, 0))
        {
            m_deltaPos = { -1,0 };
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && 
            m_deltaPos != sf::Vector2i(-1, 0))
        {
            m_deltaPos = { 1,0 };
        }


        // Manage discrete movement
        m_snakeMoveTimer += dt;
        if (m_snakeMoveTimer >= m_snakeMovePeriod)
        {
            m_snakeMoveTimer = 0.0f;

            const sf::Vector2i nextPos = m_snake.GetNextHeadPosition(m_deltaPos);
            if (!m_board.IsInsideBoard(nextPos) || m_snake.IsInTileExceptEnd(nextPos))
            {
                m_gameOver = true;
                PlaySound(m_deathSound, "Resources/Audio/death.wav");
            }
            else
            {
                const bool eating = nextPos == m_goal.GetPosition();

                if (eating)
                {
                    m_snake.Grow();
                    if (m_snakeMovePeriod >= 0.1f)
                    {
                        m_snakeMovePeriod -= 0.01f;
                    }
                    // (*)
                }

                m_snake.Move(m_deltaPos);

                // If we respawn inside de other of (*), is possible that goal 
                // respawn left to snake and in that case goal won't be eaten!
                if (eating)
                {
                    m_goal.Respawn(m_random, m_board, m_snake);
                    AddScore();
                    PlaySound(m_growSound, "Resources/Audio/grow.wav");
                }
            }
        }
    }
}

void Game::AddScore()
{
    m_score++;
    m_scoreText.setString("Score: " + std::to_string(m_score));
}

void Game::PlaySound(sf::Sound& sound, const std::string& fileName)
{
    if (!m_soundBuffer.loadFromFile(fileName))
    {
        sf::err() << "Error al cargar archivo " << fileName << "\n";
    }
    else
    {
        sound.setBuffer(m_soundBuffer);
        sound.play();
    }
}
