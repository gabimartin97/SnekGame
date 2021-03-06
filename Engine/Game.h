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
#include "FrameTimer.h"
#include "Sound.h"
#include "SoundEffect.h"
#include "GameSettings.h"



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
	void GenerateRandomApples();
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;  //Objeto gr�fico de la clase Graphics. Sus m�todos permiten manipular los pixeles de la pantalla.
	/********************************/
	GameSettings gameSettings; //Recordar que el orden de las variables importa a la hora de llamar al constructor de Game
	Board board;
	FrameTimer frameTimer;
	std::random_device dev; //seed?
	std::mt19937 rng; //random number generator 
	std::uniform_int_distribution<int> boardDistX;
	std::uniform_int_distribution<int> boardDistY;
	 int maxStones;
	 int maxPoison;
	 int maxApples;
	 float minSnekPeriod;
	static constexpr int pointsForStone = 2;
	static constexpr int pointsForSpeedBoost = 2;
	 
	Snake snek;
	Location delta_loc = { 1, 0 };
	SoundEffect pedo;
	Sound appleEaten;
	 
	float time = 0;
	float snekTime = 0;
	int points = 0;
	float snakeMoveByPeriod = 0.25f; //In seconds
	bool keyAlreadyPressed = false;
	bool isGameOver = false;
	bool isGameStarted = false;
	 int stonesSpawned = 0;
	 int poisonSpawned = 0;
	

	
	
	/********************************/
};