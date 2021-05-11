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
	// User functions here

	//
private:
	sf::RenderWindow window;
	sf::Event e;

	bool running = true;

	static constexpr int screenWidth = 800;
	static constexpr int screenHeight = 600;

	// User variables here
	sf::Clock dtClock;
	std::mt19937 random;

	Board board;
	Snake snake;
	Goal goal;
	sf::Vector2i deltaPos = { 1,0 };

	float snakeMovePeriod = 0.3f;
	float snakeMoveTimer = 0.0f;
	float dt;

	bool gameOver = false;
	//
};