#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

class Board
{
public:
	// Constructor
	Board(
		sf::RenderTarget& target, const sf::Vector2f& position, 
		const sf::Color& borderColor, float borderSize, float padding = 2.0f
	);

	// Render
	void RenderCell(const sf::Vector2i& cellPos, sf::Color color);
	void RenderBorder();

	// Functions
	bool IsInsideBoard(const sf::Vector2i cellPos) const;
																		       
	// Getters
	const int GetWidth() const { return s_width; }
	const int GetHeight() const { return s_height; }

private:
	// Graphics
	sf::RenderTarget& m_target;

	// Position and size
	sf::Vector2f m_position;
	static constexpr int s_width = 35;
	static constexpr int s_height = 25;
	static constexpr int s_cellSize = 20;
	
	// Cells
	std::vector<sf::RectangleShape> m_cells;

	// Border
	sf::RectangleShape m_border;
	sf::Color m_borderColor;
	float m_borderSize;
	float m_padding;
};

