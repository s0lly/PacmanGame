#include "Board.h"

void Board::Draw(Graphics& gfx, Level& level, Pacman& pacman, Ghosts& ghosts, int numGhosts)
{
	DrawLevel(gfx, level);

	DrawGhosts(gfx, ghosts);

	DrawPacman(gfx, pacman);
}

void Board::DrawLevel(Graphics & gfx, Level& level)
{
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (level.GetCurrentMap()[j * width + i] == 4)
			{
				DrawWall4(gfx, i, j);

				// Draw connections between walls
			}
			if (level.GetCurrentMap()[j * width + i] == 5)
			{
				DrawWall5(gfx, i, j);

				// Draw connections between walls
			}
			if (level.GetCurrentMap()[j * width + i] == 6)
			{
				DrawWall6(gfx, i, j);

				// Draw connections between walls
			}
			if (level.GetCurrentMap()[j * width + i] == 7)
			{
				DrawWall7(gfx, i, j);

				// Draw connections between walls
			}

			if (level.GetCurrentMap()[j * width + i] == 8)
			{
				DrawWall8(gfx, i, j);

				// Draw connections between walls
			}

			if (level.GetCurrentMap()[j * width + i] == 9)
			{
				DrawWall9(gfx, i, j);

				// Draw connections between walls
			}


			if (level.GetCurrentMap()[j * width + i] == 1)
			{
				DrawWall(gfx, i, j);
			
				// Draw connections between walls
			}
			
			if (level.GetCurrentMap()[j * width + i] == 0)
			{
				DrawPellet(gfx, i, j);

				// Draw connections between walls
			}

			if (level.GetCurrentMap()[j * width + i] == 3)
			{
				DrawPowerup(gfx, i, j);

				// Draw connections between walls
			}
		}
	}
}

void Board::DrawWall4(Graphics& gfx, int i, int j)
{
	gfx.PutRect(i * cellSize + wallPadding * 3, offsetUp + j * cellSize + wallPadding * 3, cellSize - wallPadding * 3, cellSize - wallPadding * 6, wallColor);
	gfx.PutRect(i * cellSize + wallPadding * 3, offsetUp + j * cellSize, cellSize - wallPadding * 6, cellSize - wallPadding * 3, wallColor);
}

void Board::DrawWall5(Graphics& gfx, int i, int j)
{
	gfx.PutRect(i * cellSize + wallPadding * 3, offsetUp + j * cellSize + wallPadding * 3, cellSize - wallPadding * 3, cellSize - wallPadding * 6, wallColor);
	gfx.PutRect(i * cellSize + wallPadding * 3, offsetUp + j * cellSize + wallPadding * 3, cellSize - wallPadding * 6, cellSize - wallPadding * 3, wallColor);
}

void Board::DrawWall6(Graphics& gfx, int i, int j)
{
	gfx.PutRect(i * cellSize, offsetUp + j * cellSize + wallPadding * 3, cellSize - wallPadding * 3, cellSize - wallPadding * 6, wallColor);
	gfx.PutRect(i * cellSize + wallPadding * 3, offsetUp + j * cellSize + wallPadding * 3, cellSize - wallPadding * 6, cellSize - wallPadding * 3, wallColor);
}

void Board::DrawWall7(Graphics& gfx, int i, int j)
{
	gfx.PutRect(i * cellSize, offsetUp + j * cellSize + wallPadding * 3, cellSize - wallPadding * 3, cellSize - wallPadding * 6, wallColor);
	gfx.PutRect(i * cellSize + wallPadding * 3, offsetUp + j * cellSize, cellSize - wallPadding * 6, cellSize - wallPadding * 3, wallColor);
}

void Board::DrawWall8(Graphics& gfx, int i, int j)
{
	gfx.PutRect(i * cellSize, offsetUp + j * cellSize + wallPadding * 3, cellSize, cellSize - wallPadding * 6, wallColor);
}

void Board::DrawWall9(Graphics& gfx, int i, int j)
{
	gfx.PutRect(i * cellSize + wallPadding * 3, offsetUp + j * cellSize, cellSize - wallPadding * 6, cellSize, wallColor);
}

void Board::DrawWall(Graphics& gfx,int i, int j)
{
	gfx.PutRect(i * cellSize + wallPadding, offsetUp + j * cellSize + wallPadding, cellSize - wallPadding * 2, cellSize - wallPadding * 2, Colors::Red);
}

void Board::DrawPellet(Graphics& gfx, int i, int j)
{
	gfx.PutRect((int)((i + 0.5) * cellSize + 0.5 - pelletSize / 2), offsetUp + (int)((j + 0.5) * cellSize - pelletSize / 2), pelletSize, pelletSize, pelletColor);
}

void Board::DrawPowerup(Graphics& gfx, int i, int j)
{
	gfx.PutCircle((int)((float)((i + 0.5f) * cellSize)), offsetUp + (int)((float)((j + 0.5f) * cellSize)), cellSize / 3, pelletColor);
}

void Board::DrawPacman(Graphics& gfx, Pacman& pacman)
{
	if (pacman.IsMouthOpen() && !pacman.GetDirection().Equiv(DIRECTION::NONE))
	{
		gfx.PutCircleSliced((int)(pacman.GetGameLoc().x * (float)cellSize), offsetUp + (int)(pacman.GetGameLoc().y * (float)cellSize), (int)(((float)cellSize / 2.0f + (float)wallPadding * 2.0f) * pacman.GetScale()) , pacman.GetColor(), pacman.GetDirection());
	}
	else
	{
		gfx.PutCircle((int)(pacman.GetGameLoc().x * (float)cellSize), offsetUp + (int)(pacman.GetGameLoc().y * (float)cellSize), (int)(((float)cellSize / 2.0f + (float)wallPadding * 2.0f) * pacman.GetScale()), pacman.GetColor());
	}
	
}

void Board::DrawGhosts(Graphics& gfx, Ghosts& ghosts)
{

	int numGhosts = ghosts.GetNumber();

	for (int i = 0; i < numGhosts; i++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
			{
				if (ghosts.GetObjectMapState(i, x, y) == 1)
				{
					gfx.PutRect((int)(ghosts.GetGameLoc(i).x * (float)cellSize) + x * 3, offsetUp + (int)(ghosts.GetGameLoc(i).y * (float)cellSize) + y * 3, 3, 3, ghosts.GetColor(i));
				}
			}
		}



		for (int y = 0; y < 9; y++)
		{
			for (int x = 0; x < 9; x++)
			{
				if (ghosts.GetEyeMapState(i, x, y) == 1)
				{
					gfx.PutRect((int)(ghosts.GetGameLoc(i).x * (float)cellSize) + x * 1 + 5, offsetUp + (int)(ghosts.GetGameLoc(i).y * (float)cellSize) + y * 1 + 5, 1, 1, { 255, 255, 255 });
				}
				if (ghosts.GetEyeMapState(i, x, y) == 2)
				{
					gfx.PutRect((int)(ghosts.GetGameLoc(i).x * (float)cellSize) + x * 1 + 5, offsetUp + (int)(ghosts.GetGameLoc(i).y * (float)cellSize) + y * 1 + 5, 1, 1, { 0, 0, 0 });
				}
			}
		}

		for (int y = 0; y < 9; y++)
		{
			for (int x = 0; x < 9; x++)
			{
				if (ghosts.GetEyeMapState(i, x, y) == 1)
				{
					gfx.PutRect((int)(ghosts.GetGameLoc(i).x * (float)cellSize) + x * 1 + 15, offsetUp + (int)(ghosts.GetGameLoc(i).y * (float)cellSize) + y * 1 + 5, 1, 1, { 255, 255, 255 });
				}
				if (ghosts.GetEyeMapState(i, x, y) == 2)
				{
					gfx.PutRect((int)(ghosts.GetGameLoc(i).x * (float)cellSize) + x * 1 + 15, offsetUp + (int)(ghosts.GetGameLoc(i).y * (float)cellSize) + y * 1 + 5, 1, 1, { 0, 0, 0 });
				}
			}
		}
	}
}
