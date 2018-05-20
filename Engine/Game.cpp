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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	eatingSound(L"coin.wav"),
	musicSound(L"03 Chibi Ninja.wav"),
	startMusicSound(L"01 A Night Of Dizzy Spells.wav")
{
}

bool Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();

	return exitGame;
}

void Game::UpdateModel()
{
	if (!gameStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			startMusicSound.StopAll();
			gameStarted = true;
			start = std::chrono::system_clock::now();
			musicSound.Play(1.0f, 0.3f);
			ghosts.Init();
			pacman.Init();
		}
		else
		{
			if (!startScreenMusicStarted)
			{
				Sleep(2000); // can remove
				startMusicSound.Play(1.0f, 0.3f);
				startScreenMusicStarted = true;
				scoreboard.Init();
				pacman.InitStartScreen();
				ghosts.InitStartScreen();
			}
			else
			{
				pacman.UpdateStartScreen();
				ghosts.UpdateStartScreen();
			}
			
		}
	}
	else
	{
		if (!gameOver)
		{
			for (int counter = 0; counter < 1; counter++)
			{
				end = std::chrono::system_clock::now();
				std::chrono::duration<float> elapsedTime = end - start;
				start = end;
				float dt = elapsedTime.count();

				if (pacman.GetLives() >= 0)
				{
					pacman.Update(wnd.kbd, level, ghosts, dt, eatingSound);
					ghosts.Update(level, dt);
					scoreboard.UpdateHighScore(pacman.GetScore());
				}
				else
				{
					gameOver = true;
				}

			}
		}
		else
		{
			if (!highScoreSaved)
			{

				scoreboard.SaveHighScore(pacman.GetScore());

				highScoreSaved = true;
			}

			if (wnd.kbd.KeyIsPressed(VK_RETURN))
			{
				exitGame = true;
			}
		}
	}
}

void Game::ComposeFrame()
{
	if (!gameStarted)
	{
		startScreen.Draw(gfx, pacman, ghosts);
	}
	else
	{
		scoreboard.DrawHighScore(gfx);
		scoreboard.DrawScore(gfx, pacman);
	
		if (!gameOver)
		{
			if (pacman.GetLives() >= 0)
			{
				board.Draw(gfx, level, pacman, ghosts, numGhosts);
				
				scoreboard.DrawLives(gfx, pacman);
			}
		}
		else
		{
			endScreen.Draw(gfx);
		}
	}
}
