#pragma once

#include "Snake.h"
#include <random>

class Goal
{
public:
	// Constructor
	Goal(std::mt19937& random, const Board& board, const Snake& snake);

	// Functions
	void Respawn(std::mt19937& random, const Board& board, const Snake& snake);

	// Render
	void Render(Board& board);

	// Getters
	const sf::Vector2i GetPosition() const { return m_position; }

private:
	sf::Vector2i m_position;
	sf::Color m_color = sf::Color::Red;
};

