/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include <random>
#include "Snake.h"
#include "Apple.h"
#include "Obstacle.h"
#include "FrameTimer.h"
#include "Poison.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	void ManageSnakeMovement();
	void ResetGame();
	void GenerateRandomPoison();
	void GenerateRadomApples();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;  //Objeto gráfico de la clase Graphics. Sus métodos permiten manipular los pixeles de la pantalla.
	/********************************/
	Board board;
	FrameTimer frameTimer;
	std::random_device dev; //seed?
	std::mt19937 rng; //random number generator 
	std::uniform_int_distribution<int> boardDistX;
	std::uniform_int_distribution<int> boardDistY;
	std::uniform_int_distribution<int> PoisonDist;
	static constexpr int maxStones = 50;
	static constexpr int maxPoison = 576;
	static constexpr int maxApples = 5;
	static constexpr int pointsForStone = 2;
	static constexpr int pointsForSpeedBoost = 2;
	Snake snek;
	Apple apples[maxApples];
	Obstacle stone[maxStones];
	Poison poison[maxPoison];
	Location delta_loc = { 0, 1 };

	float time = 0;
	float snekTime = 0;
	int points = 0;
	float snakeMoveByPeriod = 0.4f; //In seconds
	bool keyAlreadyPressed = false;
	bool isGameOver = false;
	bool isGameStarted = false;
	unsigned int stonesSpawned = 0;
	unsigned int poisonSpawned = 0;
	

	
	
	/********************************/
};