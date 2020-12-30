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
		obstacleMatrix[i] = 0 ;
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
	return obstacleMatrix[(loc.y * width) + loc.x];
}

unsigned int Board::GetObstacleIndex(const Location & loc)
{
	return obstacleMatrixIndexes[(loc.y * width) + loc.x];
}

void Board::WriteObstacle(const Location & loc, const unsigned int type_in, const unsigned int index_in)
{
	obstacleMatrix[(loc.y * width) + loc.x] = type_in;
	obstacleMatrixIndexes[(loc.y * width) + loc.x] = index_in;
}

void Board::DeleteObstacle(const Location & loc)
{
	obstacleMatrix[(loc.y * width) + loc.x] = 0;
	obstacleMatrixIndexes[(loc.y * width) + loc.x] = 0;
}

void Board::SpawnObject(const Location & loc, const int type)
{
	obstacleMatrix[(loc.y * width) + loc.x] = type;
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
