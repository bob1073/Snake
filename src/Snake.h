#pragma once

#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		// Init
		void InitHead(const sf::Vector2i& cellPos);
		void InitBody(const sf::Color& color);

		// Functions
		void Follow(const Segment& nextSegment);
		void Move(const sf::Vector2i& deltaPos);

		// Render
		void Render(Board& board);

		// Getters
		const sf::Vector2i& GetPosition() const;

	private:
		sf::Vector2i position;
		sf::Color color;
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
	static constexpr int nSegmentsMax = 100;
	
	Segment segments[nSegmentsMax];
	int nSegments = 1;
};

