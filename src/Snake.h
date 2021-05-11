#pragma once

#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const sf::Vector2i& cellPos);
		void InitBody(const sf::Color& color);
		void Follow(const Segment& nextSegment);
		void Move(const sf::Vector2i& deltaPos);
		void Render(Board& board);

		const sf::Vector2i& GetPosition() const;

	private:
		sf::Vector2i position;
		sf::Color color;
	};

public:
	Snake(const sf::Vector2i& position);

	void Move(const sf::Vector2i& deltaPos);
	sf::Vector2i GetNextHeadPosition(const sf::Vector2i& deltaPos);
	void Grow();
	void Render(Board& board);

	bool IsInTileExceptEnd(const sf::Vector2i tilePos) const;
	bool IsInTile(const sf::Vector2i& tilePos) const;

private:
	static constexpr int nSegmentsMax = 100;

	Segment segments[nSegmentsMax];
	int nSegments = 1;
};

