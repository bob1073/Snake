#include "Board.h"

Board::Board(sf::RenderTarget& target, const sf::Vector2f& position, const sf::Color& borderColor, float borderSize, float padding)
    :
    target(target),
    position(position),
    borderColor(borderColor),
    borderSize(borderSize),
    padding(padding)
{
    border.setPosition(position);
    border.setSize(sf::Vector2f(width * cellSize, height * cellSize));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(borderColor);
    border.setOutlineThickness(borderSize);

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            cells[i][j].setPosition(position.x + i * cellSize, position.y + j * cellSize);
            cells[i][j].setSize(sf::Vector2f(cellSize, cellSize));
            cells[i][j].setOutlineThickness(-padding);
            cells[i][j].setOutlineColor(sf::Color::Black);
        }
    }
}

void Board::RenderCell(const sf::Vector2i& cellPos, sf::Color color)
{
    const int x = cellPos.x;
    const int y = cellPos.y;

    cells[x][y].setFillColor(color);
    target.draw(cells[x][y]);   
}

void Board::RenderBorder()
{
    target.draw(border);
}

int Board::GetWitdh() const
{
    return width;
}

int Board::GetHeight() const
{
    return height;
}

bool Board::IsInsideBoard(const sf::Vector2i cellPos) const
{
    return cellPos.x >= 0 && cellPos.x < width&&
        cellPos.y >= 0 && cellPos.y < height;
}

