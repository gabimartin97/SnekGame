#pragma once
#include "Graphics.h"
#include "Location.h"
#include <assert.h>
#include <iostream>
#include "GameSettings.h"

class Board
{

public:
	enum class CellObjects
	{
		EmptyBoard,
		Stone,
		Poison,
		Apples,
		Snek
 
	};
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
	Board(Graphics& gfx_in, GameSettings& settings);
	~Board();
	Board(const Board&) = delete;
	Board& operator=(const Board&) = delete;
	void Resetboard();
	void DrawCell(const Location& loc, Color c);
	void DrawSmallCell(const Location& loc, Color c);
	void DrawBorders() const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	CellObjects CheckForObject(const Location& loc)const;
		
	void SpawnObject(const Location& loc, CellObjects type);
	void DespawnObject(const Location& loc);
	void DrawAllObjects();
	void UpdateObjects();
private:

	int width;	// Ancho de tablero en cantidad de celdas
	int height;	// Alto de tablero en cantidad de celdas
	int dimension; //dimensión de cada celda
	int originX;
	int originY;
	
	static constexpr int borderWidth = 2;
	static constexpr Color BorderColor = Colors::Red;
	CellObjects* objectMatrix = nullptr;
	
	Graphics& gfx;
	Apple apple;
};


