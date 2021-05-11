#pragma once

#include "Snake.h"
#include <random>

class Goal
{
public:
	Goal(std::mt19937& random, const Board& board, const Snake& snake);

	void Respawn(std::mt19937& random, const Board& board, const Snake& snake);
	void Render(Board& board);

	const sf::Vector2i GetPosition() const;

private:
	sf::Color color = sf::Color::Red;
	sf::Vector2i position;
};

