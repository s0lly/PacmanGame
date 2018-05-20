#include "EndScreen.h"

void EndScreen::Draw(Graphics & gfx)
{

	for (int i = 0; i < 4; i++)
	{
		for (int y = 0; y < titleMapHeight; y++)
		{
			for (int x = 0; x < titleMapWidth; x++)
			{
				if (endMap0[i][y * titleMapWidth + x] == 1)
				{
					gfx.PutRect(40 + titleXOffset + i * (titleXBuffer + (titleMapWidth * titleMapCellSize / 1)) + x * titleMapCellSize / 1, 300 + titleYOffset + y * titleMapCellSize / 1, titleMapCellSize / 1, titleMapCellSize / 1, c);
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int y = 0; y < titleMapHeight; y++)
		{
			for (int x = 0; x < titleMapWidth; x++)
			{
				if (endMap1[i][y * titleMapWidth + x] == 1)
				{
					gfx.PutRect(40 + titleXOffset + i * (titleXBuffer + (titleMapWidth * titleMapCellSize / 1)) + x * titleMapCellSize / 1, 400 + titleYOffset + y * titleMapCellSize / 1, titleMapCellSize / 1, titleMapCellSize / 1, c);
				}
			}
		}
	}

	for (int i = 0; i < 19; i++)
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
