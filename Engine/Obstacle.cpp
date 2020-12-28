#include "Obstacle.h"


void Obstacle::Draw(Board & board) const
{
	board.DrawCell(loc, c);
}

void Obstacle::Spawn(int x, int y, Board& board, const unsigned int index)
{
	loc.x = x;
	loc.y = y;
	board.WriteObstacle(loc, obstacleType, index);
		
}

void Obstacle::Spawn(const Location & loc_in, Board& board, const unsigned int index)
{
	Spawn(loc_in.x, loc_in.y, board, index);
}

Location Obstacle::GetLocation() const
{
	return loc;
}
