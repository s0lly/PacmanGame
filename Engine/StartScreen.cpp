#include "StartScreen.h"

void StartScreen::Draw(Graphics& gfx, Pacman& pacman, Ghosts& ghosts)
{
	DrawTitle(gfx);

	DrawPacman(gfx, pacman);

	DrawGhosts(gfx, ghosts);


}

void StartScreen::DrawTitle(Graphics & gfx)
{

	for (int i = 0; i < 6; i++)
	{
		for (int y = 0; y < titleMapHeight; y++)
		{
			for (int x = 0; x < titleMapWidth; x++)
			{
				if (titleMap0[i][y * titleMapWidth + x] == 1)
				{
					gfx.PutRect(titleXOffset + i * (titleXBuffer + (titleMapWidth * titleMapCellSize)) + x * titleMapCellSize, titleYOffset + y * titleMapCellSize, titleMapCellSize, titleMapCellSize, c);
				}
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int y = 0; y < titleMapHeight; y++)
		{
			for (int x = 0; x < titleMapWidth; x++)
			{
				if (titleMap1[i][y * titleMapWidth + x] == 1)
				{
					gfx.PutRect(100 + titleXOffset + i * (titleXBuffer + (titleMapWidth * titleMapCellSize / 3)) + x * titleMapCellSize / 3, 70 + titleYOffset + y * titleMapCellSize / 3, titleMapCellSize / 3, titleMapCellSize / 3, c);
				}
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int y = 0; y < titleMapHeight; y++)
		{
			for (int x = 0; x < titleMapWidth; x++)
			{
				if (titleMap2[i][y * titleMapWidth + x] == 1)
				{
					gfx.PutRect(60 + titleXOffset + i * (titleXBuffer + (titleMapWidth * titleMapCellSize / 2)) + x * titleMapCellSize / 2, 120 + titleYOffset + y * titleMapCellSize / 2, titleMapCellSize / 2, titleMapCellSize / 2, c);
				}
			}
		}
	}


	for (int i = 0; i < 20; i++)
	{
		for (int y = 0; y < titleMapHeight; y++)
		{
			for (int x = 0; x < titleMapWidth; x++)
			{
				if (titleMap3[i][y * titleMapWidth + x] == 1)
				{
					gfx.PutRect(-70 + titleXOffset + i * (titleXBuffer + (titleMapWidth * titleMapCellSize / 3)) + x * titleMapCellSize / 3, 700 + titleYOffset + y * titleMapCellSize / 3, titleMapCellSize / 3, titleMapCellSize / 3, c);
				}
			}
		}
	}

}

void StartScreen::DrawPacman(Graphics & gfx, Pacman & pacman)
{
	if (pacman.IsMouthOpen() && !pacman.GetDirection().Equiv(DIRECTION::NONE))
	{
		gfx.PutCircleSliced((int)(pacman.GetGameLoc().x * (float)cellSize), offsetUp + (int)(pacman.GetGameLoc().y * (float)cellSize), cellSize / 2 + wallPadding * 2, pacman.GetColor(), pacman.GetDirection());
	}
	else
	{
		gfx.PutCircle((int)(pacman.GetGameLoc().x * (float)cellSize), offsetUp + (int)(pacman.GetGameLoc().y * (float)cellSize), cellSize / 2 + wallPadding * 2, pacman.GetColor());
	}
}




void StartScreen::DrawGhosts(Graphics& gfx, Ghosts& ghosts)
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




