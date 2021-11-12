#pragma once

#include <vector>

#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		// Constructors
		Segment(const sf::Vector2i& cellPos); // Head
		Segment(const sf::Color& color1, const sf::Color& color2, std::size_t numSegments); // Body

		// Functions
		void Follow(const Segment& nextSegment);
		void Move(const sf::Vector2i& deltaPos);

		// Render
		void Render(Board& board);

		// Getters
		const sf::Vector2i& GetPosition() const { return m_position; };

	private:
		sf::Vector2i m_position;
		sf::Color m_color;
	};

public:
	// Constructor
	Snake(const sf::Vector2i& position);

	// Functions
	void Move(const sf::Vector2i& deltaPos);
	void Grow();
	bool IsInTileExceptEnd(const sf::Vector2i tilePos) const;
	bool IsInTile(const sf::Vector2i& tilePos) const;
	sf::Vector2i GetNextHeadPosition(const sf::Vector2i& deltaPos);

	// Render
	void Render(Board& board);

private:
	std::vector<Segment> m_segments;
	sf::Color m_headColor{ sf::Color::Yellow };
	sf::Color m_bodyColor1{ sf::Color::Green };
	sf::Color m_bodyColor2{ sf::Color{ 163, 73, 164 } }; // Purple
};

