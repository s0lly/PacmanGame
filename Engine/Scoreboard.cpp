#include "Scoreboard.h"
#include <iostream>
#include <iomanip>
#include <fstream>


void Scoreboard::Init()
{
	std::ifstream txtHighScore;

	txtHighScore.open("highscore.txt");
	if (!txtHighScore)
	{
		highScore = 0;
	}
	else
	{
		txtHighScore >> highScore;
	}

	txtHighScore.close();

}

void Scoreboard::DrawScore(Graphics & gfx, Pacman & pacman)
{
	int score = pacman.GetScore();

	int digits[numNums] = { 0 };

	digits[3] = score % 10;
	digits[2] = (score / 10) % 10;
	digits[1] = (score / 100) % 10;
	digits[0] = (score / 1000) % 10;

	for (int i = 0; i < 3; i++)
	{
		for (int y = 0; y < numMapHeight; y++)
		{
			for (int x = 0; x < numMapWidth; x++)
			{
				if (p1Map[i][y * numMapWidth + x] == 1)
				{
					gfx.PutRect(numXOffset + i * (numXBuffer + (numMapWidth * numMapCellSize)) + x * numMapCellSize, numYOffset + y * numMapCellSize, numMapCellSize, numMapCellSize, c);
				}
			}
		}
	}

	for (int i = 0; i < numNums; i++)
	{
		for (int y = 0; y < numMapHeight; y++)
		{
			for (int x = 0; x < numMapWidth; x++)
			{
				if (numMap[digits[i]][y * numMapWidth + x] == 1)
				{
					gfx.PutRect(numXOffset + (i + 3) * (numXBuffer + (numMapWidth * numMapCellSize)) + x * numMapCellSize, numYOffset + y * numMapCellSize, numMapCellSize, numMapCellSize, c);
				}
			}
		}
	}
}


void Scoreboard::DrawHighScore(Graphics & gfx)
{
	int score = highScore;

	int digits[numNums] = { 0 };

	digits[3] = score % 10;
	digits[2] = (score / 10) % 10;
	digits[1] = (score / 100) % 10;
	digits[0] = (score / 1000) % 10;

	for (int i = 0; i < 3; i++)
	{
		for (int y = 0; y < numMapHeight; y++)
		{
			for (int x = 0; x < numMapWidth; x++)
			{
				if (hsMap[i][y * numMapWidth + x] == 1)
				{
					gfx.PutRect(390 + numXOffset + i * (numXBuffer + (numMapWidth * numMapCellSize)) + x * numMapCellSize, numYOffset + y * numMapCellSize, numMapCellSize, numMapCellSize, c);
				}
			}
		}
	}

	for (int i = 0; i < numNums; i++)
	{
		for (int y = 0; y < numMapHeight; y++)
		{
			for (int x = 0; x < numMapWidth; x++)
			{
				if (numMap[digits[i]][y * numMapWidth + x] == 1)
				{
					gfx.PutRect(390 + numXOffset + (i + 3) * (numXBuffer + (numMapWidth * numMapCellSize)) + x * numMapCellSize, numYOffset + y * numMapCellSize, numMapCellSize, numMapCellSize, c);
				}
			}
		}
	}
}


void Scoreboard::DrawLives(Graphics & gfx, Pacman & pacman)
{
	int lives = pacman.GetLives();

	for (int i = 0; i < lives; i++)
	{
		gfx.PutCircleSliced(livesXOffset + livesXBuffer * i, livesYOffset + cellSize / 2, cellSize / 2 + wallPadding * 2, pacman.GetColor(), DIRECTION::LEFT);
	}
	
}

void Scoreboard::UpdateHighScore(int in_score)
{
	if (in_score > highScore)
	{
		highScore = in_score;
	}

}

void Scoreboard::SaveHighScore(int in_score)
{
	if (in_score >= highScore)
	{
		std::ofstream myfile;
		myfile.open("highscore.txt");

		myfile << in_score;

		myfile.close();
	}
}
