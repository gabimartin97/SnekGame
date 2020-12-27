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

void Obstacle::Spawn(const Location & loc_in)
{
	Spawn(loc_in.x, loc_in.y);
}

Location Obstacle::GetLocation() const
{
	return loc;
}
