#include "Snake.h"

Snake::Segment::Segment(const sf::Vector2i& cellPos)
{
    m_position = cellPos;
    m_color = sf::Color::Yellow;
}
Snake::Segment::Segment(const sf::Color& color1, const sf::Color& color2, std::size_t numSegments)
{
    m_color = (numSegments % 2 == 0) ? m_color = color1 : m_color = color2;
}

void Snake::Segment::Follow(const Segment& nextSegment)
{
    m_position = nextSegment.m_position;
}

void Snake::Segment::Move(const sf::Vector2i& deltaPos)
{
    const float length = static_cast<float>(
        std::sqrt(deltaPos.x * deltaPos.x + deltaPos.y * deltaPos.y)
    );
    if (length == 1.0f)
    {
        m_position += deltaPos;
    }
}

void Snake::Segment::Render(Board& board)
{
    board.RenderCell(m_position, m_color);
}

Snake::Snake(const sf::Vector2i& position)
{
    m_segments.emplace_back(position);
}

void Snake::Move(const sf::Vector2i& deltaPos)
{
    for (std::size_t i = m_segments.size() - 1; i > 0; --i)
    {
        m_segments[i].Follow(m_segments[i - 1]);
    }

    m_segments.front().Move(deltaPos);
}

void Snake::Grow()
{
    m_segments.emplace_back(m_bodyColor1, m_bodyColor2, m_segments.size());
}

bool Snake::IsInTileExceptEnd(const sf::Vector2i tilePos) const
{
    for (int i = 0; i < m_segments.size() - 1; i++)
    {
        if (m_segments[i].GetPosition() == tilePos)
        {
            return true;
        }
    }
    return false;
}

bool Snake::IsInTile(const sf::Vector2i& tilePos) const
{
    for (const auto& segment : m_segments)
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
    sf::Vector2i headPos(m_segments.front().GetPosition());
    headPos += deltaPos;
    return headPos;
}

void Snake::Render(Board& board)
{
    for (auto segment : m_segments)
    {
        segment.Render(board);
    }
}
