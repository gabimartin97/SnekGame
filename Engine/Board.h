#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>

class Board
{
private:
	class Apple
	{
	public:
		void Update();
		Color GetColor() const;
	private:
		Color c = Colors::Red;
		bool colorIncrement = true;
		int r = 200;
		int g = 0;
		int b = 0;
	};


public:
	Board(Graphics& gfx_in);
	void Resetboard();
	void DrawCell(const Location& loc, Color c);
	void DrawSmallCell(const Location& loc, Color c);
	void DrawBorders() const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	unsigned int CheckForObject(const Location& loc)const;
	unsigned int GetObstacleIndex(const Location& loc);
	void WriteObstacle(const Location& loc, const unsigned int type_in, const unsigned int index_in);
	void DeleteObstacle(const Location& loc);
	
	void SpawnObject(const Location& loc, const int type);
	void DrawAllObjects();
	void UpdateObjects();
private:
	static constexpr int originX = 100;
	static constexpr int originY = 50;
	static constexpr int width = 25;	// Ancho de tablero en cantidad de celdas
	static constexpr int height = 25;	// Alto de tablero en cantidad de celdas
	static constexpr int dimension = 20; //dimensión de cada celda
	static constexpr int borderWidth = 2;
	static constexpr Color BorderColor = Colors::Red;
	unsigned int obstacleMatrix[width * height] = { 0 };
	unsigned int obstacleMatrixIndexes[width * height] = { 0 };
	Graphics& gfx;
	Apple apple;
};


