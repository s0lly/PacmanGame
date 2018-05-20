#pragma once

#include "Level.h"
#include "Graphics.h"
#include "Colors.h"
#include "Vec2D.h"
#include "Pacman.h"
#include "Ghosts.h"

class Board
{
public:
	void Draw(Graphics& gfx, Level& level, Pacman& pacman, Ghosts& ghosts, int numGhosts);


private:
	void DrawLevel(Graphics& gfx, Level& level);

	void DrawWall4(Graphics& gfx, int i, int j);
	void DrawWall5(Graphics& gfx, int i, int j);
	void DrawWall6(Graphics& gfx, int i, int j);
	void DrawWall7(Graphics& gfx, int i, int j);
	void DrawWall8(Graphics& gfx, int i, int j);
	void DrawWall9(Graphics& gfx, int i, int j);
	void DrawWall(Graphics& gfx, int i, int j);

	void DrawPellet(Graphics & gfx, int i, int j);

	void DrawPowerup(Graphics & gfx, int i, int j);

	void DrawPacman(Graphics& gfx, Pacman& pacman);

	void DrawGhosts(Graphics& gfx, Ghosts& ghosts);


private:
	const int offsetUp = 100;
	const int width = 28;
	const int height = 31;
	const int cellSize = 25;
	const Color wallColor = Colors::Blue;
	const int wallPadding = 2;
	const Color pelletColor = Colors::Yellow;
	const int pelletSize = 4;

};