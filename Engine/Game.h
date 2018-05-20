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
#include "Level.h"
#include "Pacman.h"
#include "Ghosts.h"
#include "Sound.h"
#include "Scoreboard.h"
#include "StartScreen.h"
#include "EndScreen.h"
#include <chrono>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	bool Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	/********************************/
	static constexpr int numGhosts = 6;
	Board board;
	Level level;
	Pacman pacman;
	Ghosts ghosts;
	bool gameStarted = false;
	bool gameOver = false;
	bool startScreenMusicStarted = false;
	bool highScoreSaved = false;
	bool exitGame = false;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	Sound eatingSound;
	Sound musicSound;
	Sound startMusicSound;

	Scoreboard scoreboard;

	StartScreen startScreen;

	EndScreen endScreen;

};