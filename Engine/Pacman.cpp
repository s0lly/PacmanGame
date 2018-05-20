#include "Pacman.h"

void Pacman::Init()
{
	gameLoc = startLoc;
	direction = { 0.0f, 0.0f };
	moveBuffer = { 0.0f, 0.0f };

	initilising = true;

}

void Pacman::Update(Keyboard & kbd, Level& level, Ghosts& ghosts, float dt, Sound& eatingSound)
{

	if (initilising)
	{
		initStateTimerCurrent += initStateTimerTick;
		scale = scale / 0.75;
		scale = scale > 1.0f ? 1.0f : scale;

		if (initStateTimerCurrent >= initStateTimerMax)
		{
			initilising = false;
			initStateTimerCurrent = 0.0f;

			ghosts.Unfreeze();

			scale = 1.0f;
		}
	}
	else
	{

		float gameSpeedTick = speed * dt;

		gameSpeedTick = gameSpeedTick > 0.8f ? 0.8f : gameSpeedTick;

		if (!lifeLostState)
		{
			if (kbd.KeyIsPressed(VK_LEFT))
			{
				if (!isLeftPressed)
				{
					isLeftPressed = true;
					moveBuffer = DIRECTION::LEFT;
				}
			}
			else
			{
				isLeftPressed = false;

				if (kbd.KeyIsPressed(VK_RIGHT))
				{
					if (!isRightPressed)
					{
						isRightPressed = true;
						moveBuffer = DIRECTION::RIGHT;
					}
				}
				else
				{
					isRightPressed = false;

					if (kbd.KeyIsPressed(VK_UP))
					{
						if (!isUpPressed)
						{
							isUpPressed = true;
							moveBuffer = DIRECTION::UP;
						}
					}
					else
					{
						isUpPressed = false;

						if (kbd.KeyIsPressed(VK_DOWN))
						{
							if (!isDownPressed)
							{
								isDownPressed = true;
								moveBuffer = DIRECTION::DOWN;
							}
						}
						else
						{
							isDownPressed = false;
						}
					}
				}
			}


			CheckCollisionWalls(level, gameSpeedTick);
			gameLoc = gameLoc + direction * gameSpeedTick;

			CheckEatingPellet(level, eatingSound);
			CheckEatingPowerup(level, ghosts);
			CheckCollisionGhosts(ghosts);

			scoreLife = score;

			if (scoreLife >= scoreLifeUp)
			{
				scoreLife -= scoreLifeUp;
				lives++;
			}

			if (poweredUp)
			{
				if (poweredUpTimerCurrent >= poweredUpTimerMax)
				{
					poweredUp = false;
					poweredUpTimerCurrent = 0.0f;
				}
				else
				{
					poweredUpTimerCurrent += poweredUpTimerTick;
				}
			}

			ghosts.SetPacmanGameLoc(gameLoc);

			if (gameLoc.x - (float)(int)gameLoc.x < 0.3f || gameLoc.x - (float)(int)gameLoc.x > 0.7f || gameLoc.y - (float)(int)gameLoc.y < 0.3f || gameLoc.y - (float)(int)gameLoc.y > 0.7f)
			{
				mouthOpen = true;
			}
			else
			{
				mouthOpen = false;
			}

		}
		else //lifeLostState == true
		{
			lifeLostStateTimerCurrent += lifeLostStateTimerTick;

			if (lifeLostStateTimerCurrent >= lifeLostStateTimerMax)
			{
				lifeLostStateTimerCurrent = 0.0f;
				lifeLostState = false;
				ghosts.Init();
				Init();
			}

			scale = scale * 0.95;
			scale = scale < 0.01f ? 0.01f : scale;

		}
		ghosts.SetPacmanGameLoc(gameLoc);

	}

}

void Pacman::CheckCollisionWalls(Level& level, float gameSpeedTick)
{
	bool isOpenLeft = false;
	bool isOpenRight = false;
	bool isOpenUp = false;
	bool isOpenDown = false;
	
	if (level.GetMapTileType(gameLoc + UL + DIRECTION::LEFT * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LL + DIRECTION::LEFT * gameSpeedTick) < 4)
	{
		isOpenLeft = true;
	}
	if (level.GetMapTileType(gameLoc + UR + DIRECTION::RIGHT * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LR + DIRECTION::RIGHT * gameSpeedTick) < 4)
	{
		isOpenRight = true;
	}
	if (level.GetMapTileType(gameLoc + UL + DIRECTION::UP * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + UR + DIRECTION::UP * gameSpeedTick) < 4)
	{
		isOpenUp = true;
	
	}
	if (level.GetMapTileType(gameLoc + LL + DIRECTION::DOWN * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LR + DIRECTION::DOWN * gameSpeedTick) < 4)
	{
		isOpenDown = true;
	}


	if (direction.Equiv(DIRECTION::LEFT) && level.GetMapTileType(gameLoc + UL + DIRECTION::UP * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + UR + DIRECTION::LEFT * gameSpeedTick + DIRECTION::UP * gameSpeedTick) < 4)
	{
		if (!moveBuffer.Equiv(DIRECTION::LEFT))
		{
			gameLoc.x = (float)(int)gameLoc.x + 0.5f;
		}
		isOpenUp = true;
	}
	if (direction.Equiv(DIRECTION::LEFT) && level.GetMapTileType(gameLoc + LL + DIRECTION::DOWN * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LR + DIRECTION::LEFT * gameSpeedTick + DIRECTION::DOWN * gameSpeedTick) < 4)
	{
		if (!moveBuffer.Equiv(DIRECTION::LEFT))
		{
			gameLoc.x = (float)(int)gameLoc.x + 0.5f;
		}
		isOpenDown = true;
	}

	if (direction.Equiv(DIRECTION::RIGHT) && level.GetMapTileType(gameLoc + UR + DIRECTION::UP * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + UL + DIRECTION::RIGHT * gameSpeedTick + DIRECTION::UP * gameSpeedTick) < 4)
	{
		if (!moveBuffer.Equiv(DIRECTION::RIGHT))
		{
			gameLoc.x = (float)(int)gameLoc.x + 0.5f;
		}
		isOpenUp = true;
	}
	if (direction.Equiv(DIRECTION::RIGHT) && level.GetMapTileType(gameLoc + LR + DIRECTION::DOWN * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LL + DIRECTION::RIGHT * gameSpeedTick + DIRECTION::DOWN * gameSpeedTick) < 4)
	{
		if (!moveBuffer.Equiv(DIRECTION::RIGHT))
		{
			gameLoc.x = (float)(int)gameLoc.x + 0.5f;
		}
		isOpenDown = true;
	}




	if (direction.Equiv(DIRECTION::UP) && level.GetMapTileType(gameLoc + UL + DIRECTION::LEFT * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LL + DIRECTION::UP * gameSpeedTick + DIRECTION::LEFT * gameSpeedTick) < 4)
	{
		if (!moveBuffer.Equiv(DIRECTION::UP))
		{
			gameLoc.y = (float)(int)gameLoc.y + 0.5f;
		}
		isOpenLeft = true;
	}
	if (direction.Equiv(DIRECTION::UP) && level.GetMapTileType(gameLoc + UR + DIRECTION::RIGHT * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LR + DIRECTION::UP * gameSpeedTick + DIRECTION::RIGHT * gameSpeedTick) < 4)
	{
		if (!moveBuffer.Equiv(DIRECTION::UP))
		{
			gameLoc.y = (float)(int)gameLoc.y + 0.5f;
		}
		isOpenRight = true;
	}

	if (direction.Equiv(DIRECTION::DOWN) && level.GetMapTileType(gameLoc + LL + DIRECTION::LEFT * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + UL + DIRECTION::DOWN * gameSpeedTick + DIRECTION::LEFT * gameSpeedTick) < 4)
	{
		if (!moveBuffer.Equiv(DIRECTION::DOWN))
		{
			gameLoc.y = (float)(int)gameLoc.y + 0.5f;
		}
		isOpenLeft = true;
	}
	if (direction.Equiv(DIRECTION::DOWN) && level.GetMapTileType(gameLoc + LR + DIRECTION::RIGHT * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + UR + DIRECTION::DOWN * gameSpeedTick + DIRECTION::RIGHT * gameSpeedTick) < 4)
	{
		if (!moveBuffer.Equiv(DIRECTION::DOWN))
		{
			gameLoc.y = (float)(int)gameLoc.y + 0.5f;
		}
		isOpenRight = true;
	}




	if (direction.Equiv(DIRECTION::LEFT) && !isOpenLeft)
	{
		gameLoc.x = (float)(int)gameLoc.x + 0.5f;
	}
	if (direction.Equiv(DIRECTION::RIGHT) && !isOpenRight)
	{
		gameLoc.x = (float)(int)gameLoc.x + 0.5f;
	}
	if (direction.Equiv(DIRECTION::UP) && !isOpenUp)
	{
		gameLoc.y = (float)(int)gameLoc.y + 0.5f;
	}
	if (direction.Equiv(DIRECTION::DOWN) && !isOpenDown)
	{
		gameLoc.y = (float)(int)gameLoc.y + 0.5f;
	}


	
	if (direction.Equiv(DIRECTION::NONE))
	{
		if ((moveBuffer.Equiv(DIRECTION::LEFT) && isOpenLeft) || (moveBuffer.Equiv(DIRECTION::RIGHT) && isOpenRight) || (moveBuffer.Equiv(DIRECTION::UP) && isOpenUp) || (moveBuffer.Equiv(DIRECTION::DOWN) && isOpenDown))
		{
			direction = moveBuffer;
		}
	}
	else
	{
		if (direction.Equiv(moveBuffer))
		{
			if ((moveBuffer.Equiv(DIRECTION::LEFT) && isOpenLeft) || (moveBuffer.Equiv(DIRECTION::RIGHT) && isOpenRight) || (moveBuffer.Equiv(DIRECTION::UP) && isOpenUp) || (moveBuffer.Equiv(DIRECTION::DOWN) && isOpenDown))
			{
				direction = moveBuffer;
			}
			else
			{
				direction = DIRECTION::NONE;
			}
		}
		else
		{
			if (direction.Equiv(DIRECTION::LEFT) && moveBuffer.Equiv(DIRECTION::RIGHT) && isOpenRight)
			{
				direction = DIRECTION::RIGHT;
			}
			else if (direction.Equiv(DIRECTION::LEFT) && moveBuffer.Equiv(DIRECTION::UP) && isOpenUp)
			{
				direction = DIRECTION::UP;
			}
			else if (direction.Equiv(DIRECTION::LEFT) && moveBuffer.Equiv(DIRECTION::DOWN) && isOpenDown)
			{
				direction = DIRECTION::DOWN;
			}
			else if (direction.Equiv(DIRECTION::LEFT) && !isOpenLeft)
			{
				direction = DIRECTION::NONE;
			}
	
			
			if (direction.Equiv(DIRECTION::RIGHT) && moveBuffer.Equiv(DIRECTION::LEFT) && isOpenLeft)
			{
				direction = DIRECTION::LEFT;
			}
			else if (direction.Equiv(DIRECTION::RIGHT) && moveBuffer.Equiv(DIRECTION::UP) && isOpenUp)
			{
				direction = DIRECTION::UP;
			}
			else if (direction.Equiv(DIRECTION::RIGHT) && moveBuffer.Equiv(DIRECTION::DOWN) && isOpenDown)
			{
				direction = DIRECTION::DOWN;
			}
			else if (direction.Equiv(DIRECTION::RIGHT) && !isOpenRight)
			{
				direction = DIRECTION::NONE;
			}
	
	
			if (direction.Equiv(DIRECTION::UP) && moveBuffer.Equiv(DIRECTION::DOWN) && isOpenDown)
			{
				direction = DIRECTION::DOWN;
			}
			else if (direction.Equiv(DIRECTION::UP) && moveBuffer.Equiv(DIRECTION::LEFT) && isOpenLeft)
			{
				direction = DIRECTION::LEFT;
			}
			else if (direction.Equiv(DIRECTION::UP) && moveBuffer.Equiv(DIRECTION::RIGHT) && isOpenRight)
			{
				direction = DIRECTION::RIGHT;
			}
			else if (direction.Equiv(DIRECTION::UP) && !isOpenUp)
			{
				direction = DIRECTION::NONE;
			}
	
	
			if (direction.Equiv(DIRECTION::DOWN) && moveBuffer.Equiv(DIRECTION::UP) && isOpenUp)
			{
				direction = DIRECTION::UP;
			}
			else if (direction.Equiv(DIRECTION::DOWN) && moveBuffer.Equiv(DIRECTION::LEFT) && isOpenLeft)
			{
				direction = DIRECTION::LEFT;
			}
			else if (direction.Equiv(DIRECTION::DOWN) && moveBuffer.Equiv(DIRECTION::RIGHT) && isOpenRight)
			{
				direction = DIRECTION::RIGHT;
			}
			else if (direction.Equiv(DIRECTION::DOWN) && !isOpenDown)
			{
				direction = DIRECTION::NONE;
			}
			
	
		}
	
	}


	
}

void Pacman::CheckEatingPellet(Level& level, Sound& eatingSound)
{
	if (level.GetMapTileType({ gameLoc.x, gameLoc.y }) == 0)
	{
		level.SetMapTileType({ gameLoc.x, gameLoc.y }, 2);
		eatingSound.Play( 1.0f, 0.1f );
		score += 1;
	}
}

void Pacman::CheckEatingPowerup(Level& level, Ghosts& ghosts)
{
	if (level.GetMapTileType({ gameLoc.x, gameLoc.y }) == 3)
	{
		level.SetMapTileType({ gameLoc.x, gameLoc.y }, 2);

		StartPowerupMode(ghosts);

		score += 5;
	}
}

void Pacman::StartPowerupMode(Ghosts& ghosts)
{
	poweredUp = true;

	for (int i = 0; i < ghosts.GetNumber(); i++)
	{
		ghosts.SetWeak(i);
	}
}

void Pacman::CheckCollisionGhosts(Ghosts& ghosts)
{
	for (int i = 0; i < ghosts.GetNumber(); i++)
	{
		Vec2D UL = { 0.001f, 0.001f };
		Vec2D UR = { 0.99f, 0.001f };
		Vec2D LR = { 0.999f, 0.999f };
		Vec2D LL = { 0.001f, 0.999f };

		Vec2D gameLocUL = ghosts.GetGameLoc(i) + UL;
		Vec2D gameLocUR = ghosts.GetGameLoc(i) + UR;
		Vec2D gameLocLR = ghosts.GetGameLoc(i) + LR;
		Vec2D gameLocLL = ghosts.GetGameLoc(i) + LL;


		if (gameLoc.x - 0.5f < gameLocUR.x && gameLoc.x + 0.5f > gameLocUL.x && gameLoc.y - 0.5f < gameLocLR.y && gameLoc.y + 0.5f > gameLocUR.y)
		{
			if (ghosts.IsEaten(i))
			{

			}
			else if (ghosts.IsWeak(i))
			{
				ghosts.SetEaten(i);
				score += 20;
			}
			else
			{
				LoseLife(ghosts);
			}
		}
	}
	

}

void Pacman::LoseLife(Ghosts& ghosts)
{
	lives -= 1;
	lifeLostState = true;
	ghosts.Freeze();
}

int Pacman::GetLives()
{
	return lives;
}

bool Pacman::isLifeLost()
{
	return lifeLostState;
}


Vec2D Pacman::GetGameLoc()
{
	return gameLoc;
}

Color Pacman::GetColor()
{
	return c;
}

bool Pacman::IsMouthOpen()
{
	return mouthOpen;
}

Vec2D Pacman::GetDirection()
{
	return direction;
}

int Pacman::GetScore()
{
	return score;
}

void Pacman::InitStartScreen()
{
	gameLoc = { 7.5f, 20.55f };
	direction = DIRECTION::RIGHT;
	moveBuffer = { 0.0f, 0.0f };

}

void Pacman::UpdateStartScreen()
{

	if (gameLoc.x < 33.5f)
	{
		if (isGoingRightStartScreen)
		{
			gameLoc.x = gameLoc.x + 0.1f;
		}
		else
		{
			if (gameLoc.x > -3.5f)
			{
				gameLoc.x = gameLoc.x - 0.1f;
			}
			else
			{
				isGoingRightStartScreen = true;
				direction = DIRECTION::RIGHT;
				gameLoc.x = -3.5f + 0.01f;
			}
		}

	}
	else
	{
		isGoingRightStartScreen = false;
		gameLoc.x = 33.5f - 0.01f;
		direction = DIRECTION::LEFT;
	}

	if (gameLoc.x - (float)(int)gameLoc.x < 0.3f || gameLoc.x - (float)(int)gameLoc.x > 0.7f || gameLoc.y - (float)(int)gameLoc.y < 0.3f || gameLoc.y - (float)(int)gameLoc.y > 0.7f)
	{
		mouthOpen = true;
	}
	else
	{
		mouthOpen = false;
	}


}

float Pacman::GetScale()
{
	return scale;
}
