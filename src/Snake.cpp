#include "Snake.h"

Snake::Segment::Segment(const sf::Vector2i& cellPos)
{
    position = cellPos;
    color = sf::Color::Yellow;
}
Snake::Segment::Segment(const sf::Color& color)
{
    this->color = color;
}

void Snake::Segment::Follow(const Segment& nextSegment)
{
    position = nextSegment.position;
}

void Snake::Segment::Move(const sf::Vector2i& deltaPos)
{
    const float length = float(std::sqrt(deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y));
    if (length == 1.0f)
    {
        position += deltaPos;
    }
}

void Snake::Segment::Render(Board& board)
{
    board.RenderCell(position, color);
}

const sf::Vector2i& Snake::Segment::GetPosition() const
{
    return position;
}

Snake::Snake(const sf::Vector2i& position)
{
    segments.emplace_back(position);
}

void Snake::Move(const sf::Vector2i& deltaPos)
{
    for (int i = segments.size() - 1; i > 0; --i)
    {
        segments[i].Follow(segments[i - 1]);
    }

    segments.front().Move(deltaPos);
}

void Snake::Grow()
{
    segments.emplace_back(sf::Color::Green);
}

bool Snake::IsInTileExceptEnd(const sf::Vector2i tilePos) const
{
    for (int i = 0; i < segments.size() - 1; i++)
    {
        if (segments[i].GetPosition() == tilePos)
        {
            return true;
        }
    }
    return false;
}

bool Snake::IsInTile(const sf::Vector2i& tilePos) const
{
    for (const auto& segment : segments)
    {
        if (segment.GetPosition() == tilePos)
        {
            return true;
        }
    }
    return false;
}

sf::Vector2i Snake::GetNextHeadPosition(const sf::Vector2i& deltaPos)
{
    sf::Vector2i headPos(segments.front().GetPosition());
    headPos += deltaPos;
    return headPos;
}

void Snake::Render(Board& board)
{
    for (auto segment : segments)
    {
        segment.Render(board);
    }
}
