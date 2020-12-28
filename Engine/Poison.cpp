#include "Poison.h"


void Poison::Draw(Board & board) const
{
	board.DrawCell(loc, c);
}

void Poison::Spawn(int x, int y, Board& board)
{
	loc.x = x;
	loc.y = y;
	board.WriteObstacle(loc, obstacleType);

}

void Poison::Spawn(const Location & loc_in, Board& board)
{
	Spawn(loc_in.x, loc_in.y, board);
}

Location Poison::GetLocation() const
{
	return loc;
}