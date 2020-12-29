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
#define Snek 4
#define Apples 3
#define Poison 2
#define Stone 1
#define EmptyBoard 0

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	board(gfx),
	rng(dev()),
	boardDistX(0, board.GetWidth() - 1),
	boardDistY(0, board.GetHeight() - 1),
	PoisonDist(0, 4),
	snek({10,18}, board)
	

{
	GenerateRandomPoison();
	GenerateRadomApples();
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
	float dt = frameTimer.Mark();
	
	

	if (isGameStarted && !isGameOver) {
		
		ManageSnakeMovement();			//Control de movimiento por teclado
		time = frameTimer.Time();
			
		for (Apple& a : apples)
		{
			a.Update();
		}
					

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
				

				switch (board.CheckForObstacle(next))
				{

				case Apples:
				{
					int appleIndex = board.GetObstacleIndex(next);

					do {
						apples[appleIndex].Respawn(boardDistX(rng), boardDistY(rng), board, appleIndex);

					} while (snek.IsInTile(apples[appleIndex].GetLocation()));
					points++;
					snek.Grow(board);
					if ((points % pointsForStone == 0) && (stonesSpawned < maxStones))
					{
						do {
							Location nextStoneLocation = { boardDistX(rng), boardDistY(rng) };
							if (nextStoneLocation == next) continue;
							stone[stonesSpawned].Spawn(nextStoneLocation, board, stonesSpawned);

						} while (snek.IsInTile(stone[stonesSpawned].GetLocation()));
						stonesSpawned++;
					}
					if (points % pointsForSpeedBoost == 0 && snakeMoveByPeriod > 0.05f) {
						snakeMoveByPeriod = snakeMoveByPeriod - 0.015f;
					}
					break;
				}
							
				case Stone:
					isGameOver = true;
					break;

				case Poison:
					if(snakeMoveByPeriod > 0.05f) snakeMoveByPeriod -= 0.025f;
					
					board.WriteObstacle(next, EmptyBoard, 0);
					break;
				
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
		
		

		for (int i = 0; i < (board.GetHeight()); i++)
		{
			for (int k = 0; k < (board.GetWidth()); k++)
			{
				switch (board.CheckForObstacle(Location{ k,i }))
				{
				case Poison:
				{
					int poisonIndex = board.GetObstacleIndex(Location{ k, i });
					poison[poisonIndex].Draw(board);
					break;
				}
				case Stone:
				{
					int stoneIndex = board.GetObstacleIndex(Location{ k, i });
					stone[stoneIndex].Draw(board);
					break;
				}
				case Apples:
				{
					int appleIndex = board.GetObstacleIndex(Location{ k, i });
					apples[appleIndex].Draw(board);
					break;
				}
				case Snek:
				{
					snek.Draw(board, board.GetObstacleIndex(Location{ k, i }));
					break;
				}
				default:
					break;

				}
			}
		}

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
	GenerateRadomApples();
}

void Game::GenerateRandomPoison()
{
	for (int i = 0; i < (board.GetHeight()); i++)
	{
		for (int k = 0; k < (board.GetWidth()); k++)
		{
			if ((board.CheckForObstacle(Location{ k,i }) == EmptyBoard) && (PoisonDist(rng) == 3) && (poisonSpawned < maxPoison))
			{
				poison[poisonSpawned].Spawn(Location{ k,i }, board, poisonSpawned);
				poisonSpawned++;
			}
		}
	}
}

void Game::GenerateRadomApples()
{
	for (int i = 0; i < maxApples; i++)
	{
		Location randomCoords = { boardDistX(rng),boardDistY(rng) };
		while (board.CheckForObstacle(randomCoords) != 0)
		{
			randomCoords = { boardDistX(rng),boardDistY(rng) };

		}
		apples[i].Spawn(randomCoords, board, i);
	}
}
	

