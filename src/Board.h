#pragma once

#include <SFML/Graphics.hpp>

class Board
{
public:
	Board(const sf::Vector2f& position, const sf::Color& borderColor, float borderSize, float padding = 2.0f);

	void RenderCell(sf::RenderTarget& target, const sf::Vector2i& cellPos, sf::Color color);
	void RenderBorder(sf::RenderTarget& target);

	int GetWitdh() const;
	int GetHeight() const;
	
	bool IsInsideBoard(const sf::Vector2i cellPos) const;

private:
	static constexpr int width = 35;
	static constexpr int height = 25;
	static constexpr int cellSize = 20;

	sf::Vector2f position;
	sf::RectangleShape border;
	sf::RectangleShape cells[width][height];

	sf::Color borderColor;
	float borderSize;
	float padding;

};

