#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>

class Board
{
public:
	Board(Graphics& gfx_in);
	void Resetboard();
	void DrawCell(const Location& loc, Color c);
	void DrawSmallCell(const Location& loc, Color c);
	void DrawBorders() const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	unsigned int CheckForObstacle(const Location& loc)const;
	void WriteObstacle(const Location& loc, const unsigned int type_in);
	void DeleteObstacle(const Location& loc);
	
private:
	static constexpr int originX = 100;
	static constexpr int originY = 50;
	static constexpr int width = 25;	// Ancho de tablero en cantidad de celdas
	static constexpr int height = 25;	// Alto de tablero en cantidad de celdas
	static constexpr int dimension = 20; //dimensión de cada celda
	static constexpr int borderWidth = 2;
	static constexpr Color BorderColor = Colors::Red;
	Graphics& gfx;
	unsigned int obstacleMatrix[width * height] = { 0 };
};


