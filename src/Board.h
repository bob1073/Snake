#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Board
{
public:
	// Constructor
	Board(sf::RenderTarget& target, const sf::Vector2f& position, const sf::Color& borderColor, float borderSize, float padding = 2.0f);

	// Render
	void RenderCell(const sf::Vector2i& cellPos, sf::Color color);
	void RenderBorder();

	// Functions
	bool IsInsideBoard(const sf::Vector2i cellPos) const;

	// Getters
	int GetWidth() const;
	int GetHeight() const;

private:
	// Graphics
	sf::RenderTarget& target;

	// Position and size
	sf::Vector2f position;
	static constexpr int width = 35;
	static constexpr int height = 25;
	static constexpr int cellSize = 20;
	
	// Cells
	std::vector<sf::RectangleShape> cells;

	// Border
	sf::RectangleShape border;
	sf::Color borderColor;
	float borderSize;
	float padding;
};

