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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	board(gfx),
	rng(dev()),
	boardDistX(0,board.GetWidth()),
	boardDistY(0, board.GetHeight()),
	snek({10,18}),
	apple({boardDistX(rng),boardDistY(rng)})

{

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
		apple.Update();

		if (time - snekTime >= snakeMoveByPeriod)
		{
			snekTime = frameTimer.Time();
			const Location next = snek.GetNextHeadLocation(delta_loc);
			snek.CheckSelfCollision(next);
			if (!board.IsInsideBoard(next) || snek.IsCollided() || board.CheckForObstacle(next))
			{
				isGameOver = true;
			}
			else
			{
				snek.MoveBy(delta_loc);

				if (snek.CheckFood(apple)) {
					do {
						apple.Respawn(boardDistX(rng), boardDistY(rng));

					} while (snek.IsInTile(apple.GetLocation()));
					snek.Grow();
					if (points % pointsForStone == 0) {
						do {
							Location nextStoneLocation = { boardDistX(rng), boardDistY(rng) };
							stone[points/pointsForStone].Spawn(nextStoneLocation, board);
							if (nextStoneLocation == next) continue;
						} while (snek.IsInTile(stone[points/pointsForStone].GetLocation()));
					}
					if (points % pointsForSpeedBoost == 0 && snakeMoveByPeriod > 0.05f) {
						snakeMoveByPeriod = snakeMoveByPeriod - 0.025f;
					}
					points++;

				}
				
				keyAlreadyPressed = false;

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
		apple.Draw(board);
		snek.Draw(board);
		for (int i = 0; i < points/pointsForStone && i < maxStones; i++)
		{
			stone[i].Draw(board);
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

	snek.ResetSnake(Location{ 3,3 });
	board.Resetboard();

}
	

