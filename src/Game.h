#pragma once

#include "Snake.h"
#include "Goal.h"

class Game
{
public:
	Game();
	~Game();

	void UpdateEvents();
	void Update();
	void Render();

	bool IsRunning() const;

	/*User functions here*/
	void UpdateSnake(const float& dt);

	/*********************/
private:
	sf::RenderWindow window;
	sf::Event e;

	bool running = true;

	static constexpr int screenWidth = 800;
	static constexpr int screenHeight = 600;

	/* User variables here */
	// Basic stuff
	sf::Clock dtClock;
	float dt;
	std::mt19937 random;

	// Game entities
	Board board;
	Snake snake;
	Goal goal;
	
	// Interface
	sf::Font font;
	sf::Text startText;
	sf::Text gameOverText;
	static constexpr int fontSize = 60;

	// Snake movement
	sf::Vector2i deltaPos = { 1,0 };
	float snakeMovePeriod = 0.3f;
	float snakeMoveTimer = 0.0f;
	
	// Game state
	bool gameOver = false;
	bool gameStart = false;
	/***********************/
};