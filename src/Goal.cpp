#include "Goal.h"

Goal::Goal(std::mt19937& random, const Board& board, const Snake& snake)
{
    Respawn(random, board, snake);
}

void Goal::Respawn(std::mt19937& random, const Board& board, const Snake& snake)
{
    std::uniform_int_distribution<int> xDist(0, board.GetWidth() - 1);
    std::uniform_int_distribution<int> yDist(0, board.GetHeight() - 1);

    sf::Vector2i newPos;

    do
    {
        newPos.x = xDist(random);
        newPos.y = yDist(random);

    } while (snake.IsInTile(newPos));

    position = newPos;
}

void Goal::Render(Board& board)
{
    board.RenderCell(position, color);
}

const sf::Vector2i Goal::GetPosition() const
{
    return position;
}
