#pragma once

#include "Snake.h"
#include "Goal.h"

class Game
{
public:
	Game();

	void UpdateEvents();
	void Update();
	void Render();

	const bool IsRunning() const { return m_running; }

	/*User functions here*/
	void UpdateSnake(float dt);
	void AddScore();
	
	void PlaySound(sf::Sound& sound, const std::string& fileName);

	/*********************/
private:
	sf::RenderWindow m_window;
	sf::Event m_event;

	bool m_running = true;

	static constexpr int s_screenWidth = 800;
	static constexpr int s_screenHeight = 600;

	/* User variables here */
	// Basic stuff
	sf::Clock m_dtClock;
	float m_dt;
	std::mt19937 m_random;

	// Game entities
	Board m_board;
	Snake m_snake;
	Goal m_goal;
	
	// Interface
	sf::Font m_font;
	sf::Text m_startText;
	sf::Text m_scoreText;
	sf::Text m_gameOverText;
	static constexpr int s_fontSize = 60;

	// Snake movement
	sf::Vector2i m_deltaPos = { 1,0 };
	float m_snakeMovePeriod = 0.3f;
	float m_snakeMoveTimer = 0.0f;
	
	// Game variables
	bool m_gameOver = false;
	bool m_gameStart = false;
	int m_score = 0;

	// Audio
	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_deathSound;
	sf::Sound m_growSound;
	/***********************/
};