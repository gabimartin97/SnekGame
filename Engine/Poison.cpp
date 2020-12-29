#include "Poison.h"


void Poison::Draw(Board & board) const
{
	board.DrawSmallCell(loc, c);
}

void Poison::Spawn(int x, int y, Board& board, const unsigned index)
{
	loc.x = x;
	loc.y = y;
	board.WriteObstacle(loc, obstacleType, index);

}

void Poison::Spawn(const Location & loc_in, Board& board, const unsigned index)
{
	Spawn(loc_in.x, loc_in.y, board, index);
}

void Poison::Despawn(Board& board)
{
	board.WriteObstacle(loc, 0, 0);
	isEaten = true;
}

bool Poison::IsEaten() const
{
	return isEaten;
}

Location Poison::GetLocation() const
{
	return loc;
}