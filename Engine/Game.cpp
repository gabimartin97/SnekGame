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
	snek({3,3}),
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
	if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
		isGameStarted = true;
	}

	if (isGameStarted && !isGameOver) {

		if (!keyAlreadyPressed) {
			if (wnd.kbd.KeyIsPressed(VK_UP)) {
				delta_loc = { 0, -1 };
				keyAlreadyPressed = true;
			}
			else
				if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
					delta_loc = { 0, 1 };
					keyAlreadyPressed = true;
				}
				else
					if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
						delta_loc = { -1, 0 };
						keyAlreadyPressed = true;
					}
					else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
					{
						delta_loc = { 1, 0 };
						keyAlreadyPressed = true;
					}
		}
		framesCounter++;
		apple.Update();

		if (framesCounter >= snakeMoveByPeriod)
		{
			const Location next = snek.GetNextHeadLocation(delta_loc);
			snek.CheckSelfCollision(next);

			for (int i = 0; i < points / pointsForStone && i < maxStones; i++)
			{
				if (next == stone[i].GetLocation())
				{
					isGameOver = true;
				}
				
			}
			if (!board.IsInsideBoard(next) || snek.IsCollided() || isGameOver)
			{
				isGameOver = true;
			}
			else {
				snek.MoveBy(delta_loc);

				if (snek.CheckFood(apple)) {
					do {
						apple.Respawn(boardDistX(rng), boardDistY(rng));

					} while (snek.IsInTile(apple.GetLocation()));
					snek.Grow();
					if (points % pointsForStone == 0) {
						do {
							stone[points/pointsForStone].Spawn(boardDistX(rng), boardDistY(rng));

						} while (snek.IsInTile(stone[points/pointsForStone].GetLocation()));
					}
					if (points % pointsForSpeedBoost == 0 && snakeMoveByPeriod >= 8) {
						snakeMoveByPeriod = snakeMoveByPeriod - 1;
					}
					points++;

				}
				framesCounter = 0;
				keyAlreadyPressed = false;

			}



		}
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

	
	

