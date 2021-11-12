#include "Board.h"

Board::Board(sf::RenderTarget& target, const sf::Vector2f& position, 
    const sf::Color& borderColor, float borderSize, float padding)
    :
    m_target{ target },
    m_position{ position },
    m_cells{ s_width * s_height },
    m_borderColor{ borderColor },
    m_borderSize{ borderSize },
    m_padding{ padding }
{
    // Init border
    m_border.setPosition(position);
    m_border.setSize(sf::Vector2f(s_width * s_cellSize, s_height * s_cellSize));
    m_border.setFillColor(sf::Color::Transparent);
    m_border.setOutlineColor(borderColor);
    m_border.setOutlineThickness(borderSize);

    // Init all cells
    for (int i = 0; i < s_width; ++i)
    {
        for (int j = 0; j < s_height; ++j)
        {
            m_cells[j * s_width + i].setPosition(position.x + i * s_cellSize, position.y + j * s_cellSize);
            m_cells[j * s_width + i].setSize(sf::Vector2f(s_cellSize, s_cellSize));
            m_cells[j * s_width + i].setOutlineThickness(-padding);
            m_cells[j * s_width + i].setOutlineColor(sf::Color::Black);
        }
    }
}

void Board::RenderCell(const sf::Vector2i& cellPos, sf::Color color)
{
    const int x = cellPos.x;
    const int y = cellPos.y;

    m_cells[y * s_width + x].setFillColor(color);
    m_target.draw(m_cells[y * s_width + x]);
}

void Board::RenderBorder()
{
    m_target.draw(m_border);
}

bool Board::IsInsideBoard(const sf::Vector2i cellPos) const
{
    return cellPos.x >= 0 && cellPos.x < s_width &&
        cellPos.y >= 0 && cellPos.y < s_height;
}


