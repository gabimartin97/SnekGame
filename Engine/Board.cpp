#include "Board.h"


Board::Board(Graphics & gfx_in)
	:
	gfx(gfx_in)
{
}

void Board::Resetboard()
{
	for (int i = 0; i < (width * height); i++)
	{
		hasObstacle[i] = false ;
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

bool Board::CheckForObstacle(const Location & loc) const
{
	return hasObstacle[(loc.y * width) + loc.x];
}

void Board::WriteObstacle(const Location & loc)
{
	hasObstacle[(loc.y * width) + loc.x] = true;
}


