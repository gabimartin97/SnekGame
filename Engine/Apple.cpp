#include "Apple.h"

Apple::Apple(const Location& loc_in, Board& board, const unsigned index) {
	loc = loc_in;
	board.WriteObstacle(loc, obstacleType, index);
}

void Apple::Draw(Board& board) const
{
	board.DrawCell(loc, c);
}

void Apple::Respawn(int x, int y, Board& board, const unsigned index)
{
	board.DeleteObstacle(loc);
	loc.x = x;
	loc.y = y;
	g = 0;
	b = 0;
	colorIncrement = true;
	board.WriteObstacle(loc, obstacleType, index);
}

void Apple::Spawn(Location& loc_in, Board& board, const unsigned index)
{
	loc = loc_in;
	board.WriteObstacle(loc, obstacleType, index);
}

void Apple::Respawn(Location & loc_in, Board & board, const unsigned index)
{
	Respawn(loc_in.x, loc_in.y, board, index);
}

void Apple::Update()
{
	if (colorIncrement)
	{
		g += 5;
		b += 5;
		if (g >= 255 || b >= 255)
		{
			colorIncrement = false;
		}
	}
	if (!colorIncrement)
	{
		g -= 5;
		b -= 5;
		if (g <= 0 || b <= 0)
		{
			colorIncrement = true;
		}
	}
	c = Colors::MakeRGB(r, g, b);
}

Location Apple::GetLocation() const
{
	return loc;
}

