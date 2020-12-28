#include "Obstacle.h"


void Obstacle::Draw(Board & board) const
{
	board.DrawCell(loc, c);
}

void Obstacle::Spawn(int x, int y, Board& board)
{
	loc.x = x;
	loc.y = y;
	board.WriteObstacle(loc, obstacleType);
		
}

void Obstacle::Spawn(const Location & loc_in, Board& board)
{
	Spawn(loc_in.x, loc_in.y, board);
}

Location Obstacle::GetLocation() const
{
	return loc;
}
