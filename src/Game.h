#pragma once

#include <SFML/Graphics.hpp>

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

	//
};