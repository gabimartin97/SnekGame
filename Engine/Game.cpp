/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	gameSettings("settings.txt"),
	maxStones(gameSettings.GetMaxStones()),
	maxPoison(gameSettings.GetMaxPosion()),
	maxApples(gameSettings.GetMaxApples()),
	minSnekPeriod(gameSettings.GetMinSnekPeriod()),
	board(gfx, gameSettings),
	rng(dev()),
	boardDistX(0, board.GetWidth() - 1),
	boardDistY(0, board.GetHeight() - 1),
	snek({12,12}, board),
	pedo({ L"Sounds\\fart2.wav", L"Sounds\\fart1.wav" }),
	appleEaten(L"Sounds\\coin.wav")

	

{
	GenerateRandomPoison();
	GenerateRandomApples();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
		
	if (isGameStarted && !isGameOver) {
		
		ManageSnakeMovement();			//Control de movimiento por teclado
		time = frameTimer.Time();
		board.UpdateObjects();
		
					

		if (time - snekTime >= snakeMoveByPeriod)
		{
			snekTime = frameTimer.Time();
			const Location next = snek.GetNextHeadLocation(delta_loc);
			snek.CheckSelfCollision(next);
			if (!board.IsInsideBoard(next) || snek.IsCollided() )
			{
				isGameOver = true;
			}
			else
			{
				switch (board.CheckForObject(next))
				{

				case Board::CellObjects::Apples:
				{

					Location randomCoords = { boardDistX(rng),boardDistY(rng) };
					while (board.CheckForObject(randomCoords) != Board::CellObjects::EmptyBoard && !(randomCoords == next))
					{
						randomCoords = { boardDistX(rng),boardDistY(rng) };
					}
					board.SpawnObject(randomCoords, Board::CellObjects::Apples);
					points++;
					snek.Grow(board);
					//appleEaten.Play();
					

					if ((points % pointsForStone == 0) && (stonesSpawned < maxStones))
					{
						Location randomCoords = { boardDistX(rng),boardDistY(rng) };
						while (board.CheckForObject(randomCoords) != Board::CellObjects::EmptyBoard && !(randomCoords == next))
						{
							randomCoords = { boardDistX(rng),boardDistY(rng) };
						}
						board.SpawnObject(randomCoords, Board::CellObjects::Stone);
						stonesSpawned++;
						
					}
					if (points % pointsForSpeedBoost == 0 && snakeMoveByPeriod > 0.05f) {
						snakeMoveByPeriod = snakeMoveByPeriod - 0.015f;
					}
					break;
				}
							
				case Board::CellObjects::Stone:
					isGameOver = true;
					break;

				case Board::CellObjects::Poison:
				{
					
					if (snakeMoveByPeriod > minSnekPeriod) snakeMoveByPeriod -= 0.01f;
					//pedo.Play(rng,0.8f);
					break;
				}
				default:
					break;
				}
			
				keyAlreadyPressed = false;
				if(!isGameOver) snek.MoveBy(delta_loc, board);

			}



		}
	}
	else
	{
		 if (isGameStarted && isGameOver && wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			ResetGame();
			wnd.kbd.Flush();
			isGameStarted = true;
		}
		 else 
			 if (wnd.kbd.KeyIsPressed(VK_RETURN)) isGameStarted = true;
		
		
	}
}

void Game::ComposeFrame()
{
	
	if (!isGameStarted) {
		SpriteCodex::DrawTitle(300,200,gfx);
	}
	else {
		board.DrawBorders();
		snek.Draw(board);
		board.DrawAllObjects();

		if (isGameOver) {
			SpriteCodex::DrawGameOver(300, 300, gfx);
		}
	}


}

void Game::ManageSnakeMovement()
{
	if (!keyAlreadyPressed) {
		if (wnd.kbd.KeyIsPressed(VK_UP)) {
			if (!(delta_loc == Location{ 0, 1 }))
			{
				delta_loc = { 0, -1 };
				keyAlreadyPressed = true;
			}
		}
		else
			if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
				if (!(delta_loc == Location{ 0, -1 }))
				{
					delta_loc = { 0, 1 };
					keyAlreadyPressed = true;
				}
			}
			else
				if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
					if (!(delta_loc == Location{ 1, 0 }))
					{
						delta_loc = { -1, 0 };
						keyAlreadyPressed = true;
					}
				}
				else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
				{
					if (!(delta_loc == Location{ -1, 0 }))
					{
						delta_loc = { 1, 0 };
						keyAlreadyPressed = true;
					}
				}
	}
}

void Game::ResetGame()
{
	time = 0;
	snekTime = 0;
	points = 0;
	snakeMoveByPeriod = 0.4f; //In seconds
	isGameOver = false;
	isGameStarted = false; 

	snek.ResetSnake(Location{ 3,3 }, board);
	board.Resetboard();
	GenerateRandomPoison();
	GenerateRandomApples();
}

void Game::GenerateRandomPoison()
{
	for (int i = 0; i < maxPoison; i++)
	{
		Location randomCoords = { boardDistX(rng),boardDistY(rng) };
		while (board.CheckForObject(randomCoords) != Board::CellObjects::EmptyBoard)
		{
			randomCoords = { boardDistX(rng),boardDistY(rng) };

		}

		board.SpawnObject(randomCoords, Board::CellObjects::Poison);
		poisonSpawned++;
	}
}

void Game::GenerateRandomApples()
{
	for (int i = 0; i < maxApples; i++)
	{
		Location randomCoords = { boardDistX(rng),boardDistY(rng) };
		while (board.CheckForObject(randomCoords) != Board::CellObjects::EmptyBoard)
		{
			randomCoords = { boardDistX(rng),boardDistY(rng) };

		}
		
		board.SpawnObject(randomCoords, Board::CellObjects::Apples);
	}
}
	

