#include "Apple.h"

Apple::Apple(const Location& loc_in) {
	loc = loc_in;

}

void Apple::Draw(Board& board) const
{
	board.DrawCell(loc, c);
}

void Apple::Respawn(int x, int y)
{
	loc.x = x;
	loc.y = y;
	g = 0;
	b = 0;
	colorIncrement = true;
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

