#include "Snake.h"

void Snake::Segment::InitHead(const sf::Vector2i& cellPos)
{
    position = cellPos;
    color = sf::Color::Yellow;
}

void Snake::Segment::InitBody(const sf::Color& color)
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
    segments[0].InitHead(position);
}

void Snake::Move(const sf::Vector2i& deltaPos)
{
    for (int i = nSegments - 1; i > 0; --i)
    {
        segments[i].Follow(segments[i - 1]);
    }

    segments[0].Move(deltaPos);
}

void Snake::Grow()
{
    if (nSegments < nSegmentsMax)
    {
        segments[nSegments].InitBody(sf::Color::Green);
        ++nSegments;
    }
}

bool Snake::IsInTileExceptEnd(const sf::Vector2i tilePos) const
{
    for (int i = 0; i < nSegments - 1; i++)
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
    for (int i = 0; i < nSegments; i++)
    {
        if (segments[i].GetPosition() == tilePos)
        {
            return true;
        }
    }
    return false;
}

sf::Vector2i Snake::GetNextHeadPosition(const sf::Vector2i& deltaPos)
{
    sf::Vector2i headPos(segments[0].GetPosition());
    headPos += deltaPos;
    return headPos;
}

void Snake::Render(Board& board)
{
    for (int i = 0; i < nSegments; ++i)
    {
        segments[i].Render(board);
    }
}
