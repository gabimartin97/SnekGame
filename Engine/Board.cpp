#include "Board.h"
#define Snek 4
#define Apples 3
#define Poison 2
#define Stone 1
#define EmptyBoard 0


Board::Board(Graphics & gfx_in)
	:
	gfx(gfx_in)
{
}

void Board::Resetboard()
{
	for (int i = 0; i < (width * height); i++)
	{
		objectMatrix[i] = 0 ;
	}
	
}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x <= width);
	assert(loc.y >= 0);
	assert(loc.y <= height);

	int x0 = originX + (loc.x * dimension);
	int y0 = originY + (loc.y * dimension);

	gfx.DrawRectDim(x0, y0, dimension, dimension, c);
}

void Board::DrawSmallCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x <= width);
	assert(loc.y >= 0);
	assert(loc.y <= height);

	int x0 = originX + loc.x  * dimension;
	int y0 = originY + loc.y * dimension;

	gfx.DrawRectDim(x0 + 1, y0 + 1, dimension - 2, dimension - 2, c);
}

void Board::DrawBorders() const
{
	
	int lowerLimit = originY + (dimension * height);
	int rightLimit = originX + (dimension * width);
	int upperLimit = originY - 1;
	int leftLimit = originX - 1;

	//Top Border
	for (int x = leftLimit; x <= rightLimit; x++) {

		for (int y = upperLimit - borderWidth; y <= upperLimit; y++) {
			gfx.PutPixel(x, y, BorderColor);
		}
	}
	//Bottom Border
	for (int x = leftLimit; x <= rightLimit; x++) {

		for (int y = lowerLimit; y <= lowerLimit + borderWidth; y++) {
			 
			gfx.PutPixel(x, y, BorderColor);
		}
	}

	//Left

	for (int x = leftLimit - borderWidth; x <= leftLimit; x++) {

		for (int y = upperLimit; y <= lowerLimit; y++) {

			gfx.PutPixel(x, y, BorderColor);
		}

	}

	//right
		for (int x = rightLimit; x <= rightLimit + borderWidth; x++) {

			for (int y = upperLimit; y <= lowerLimit; y++) {

				gfx.PutPixel(x, y, BorderColor);
			}

		}

}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}

unsigned int Board::CheckForObject(const Location & loc) const
{
	return objectMatrix[(loc.y * width) + loc.x];
}


void Board::SpawnObject(const Location & loc, const int type)
{
	objectMatrix[(loc.y * width) + loc.x] = type;
}

void Board::DespawnObject(const Location & loc)
{
	objectMatrix[(loc.y * width) + loc.x] = EmptyBoard;
}

void Board::DrawAllObjects() 
{
	for (int i = 0; i < (height); i++)
	{
		for (int k = 0; k < (width); k++)
		{
			const Location casilla = Location{ k,i };
			switch (CheckForObject(casilla))
			{
			case Poison:
			{
				DrawSmallCell(casilla, Colors::Magenta);
				break;
			}
			case Stone:
			{
				DrawSmallCell(casilla, Colors::Gray);
				
				break;
			}
			case Apples:
			{
				DrawSmallCell(casilla, apple.GetColor() );
				break;
			}
			default:
				break;

			}
		}
	}
}

void Board::UpdateObjects()
{
	apple.Update();
}

void Board::Apple::Update()
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

Color Board::Apple::GetColor() const
{
	return c;
}
