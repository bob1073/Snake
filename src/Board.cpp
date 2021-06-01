#include "Board.h"

Board::Board(sf::RenderTarget& target, const sf::Vector2f& position, const sf::Color& borderColor, float borderSize, float padding)
    :
    target(target),
    position(position),
    cells(width*height),
    borderColor(borderColor),
    borderSize(borderSize),
    padding(padding)
{
    // Init border
    border.setPosition(position);
    border.setSize(sf::Vector2f(width * cellSize, height * cellSize));
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(borderColor);
    border.setOutlineThickness(borderSize);

    // Init all cells
    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            cells[j * width + i].setPosition(position.x + i * cellSize, position.y + j * cellSize);
            cells[j * width + i].setSize(sf::Vector2f(cellSize, cellSize));
            cells[j * width + i].setOutlineThickness(-padding);
            cells[j * width + i].setOutlineColor(sf::Color::Black);
        }
    }
}

void Board::RenderCell(const sf::Vector2i& cellPos, sf::Color color)
{
    const int x = cellPos.x;
    const int y = cellPos.y;

    cells[y * width + x].setFillColor(color);
    target.draw(cells[y * width + x]);
}

void Board::RenderBorder()
{
    target.draw(border);
}

bool Board::IsInsideBoard(const sf::Vector2i cellPos) const
{
    return cellPos.x >= 0 && cellPos.x < width&&
        cellPos.y >= 0 && cellPos.y < height;
}

int Board::GetWidth() const
{
    return width;
}

int Board::GetHeight() const
{
    return height;
}

