#include "Obstacle.h"


void Obstacle::Draw(Board & board) const
{
	board.DrawCell(loc, c);
}

void Obstacle::Spawn(int x, int y)
{
	loc.x = x;
	loc.y = y;
	
}

Location Obstacle::GetLocation() const
{
	return loc;
}
