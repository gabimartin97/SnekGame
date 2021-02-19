#include "Board.h"


Board::Board(Graphics & gfx_in, GameSettings& settings)
	:
	gfx(gfx_in),
	width(settings.GetBoardWidth()),
	height(settings.GetBoardHeight()),
	dimension(settings.GetTileSize()),
	originX(((Graphics::ScreenWidth) / 2) - (width / 2 * dimension)),
	originY(((Graphics::ScreenHeight) / 2) - (height / 2 * dimension)),
	objectMatrix(int(width * height), CellObjects::EmptyBoard)
{
}

void Board::Resetboard()
{
	for (CellObjects& b : objectMatrix)
	{
		b = CellObjects::EmptyBoard ;
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

Board::CellObjects Board::CheckForObject(const Location & loc) const
{
	return objectMatrix[(loc.y * width) + loc.x];
}


void Board::SpawnObject(const Location & loc, CellObjects type)
{
	objectMatrix[(loc.y * width) + loc.x] = type;
}

void Board::DespawnObject(const Location & loc)
{
	objectMatrix[(loc.y * width) + loc.x] = CellObjects::EmptyBoard;
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
			case CellObjects::Poison:
			{
				DrawSmallCell(casilla, Colors::MakeRGB(87,0,127));
				break;
			}
			case CellObjects::Stone:
			{
				DrawSmallCell(casilla, Colors::Gray);
				
				break;
			}
			case CellObjects::Apples:
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
