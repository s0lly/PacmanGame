#include "Ghosts.h"

void Ghosts::Ghost::Init(Vec2D in_gameLoc, Color in_c, int number)
{
	gameLoc = in_gameLoc;
	initialised = true;
	p_objectMap = &objectMap[0];
	c = in_c;
	//float directionSetting = 0;
	//if (number < 2)
	//{
	//	directionSetting = -1.0f;
	//}
	//else
	//{
	//	directionSetting = -1.0f;
	//}
	//direction = { directionSetting, 0 };
	
	TurnEyes(DIRECTION::LEFT);

	eatenSound = Sound(L"EatGhost.wav");

	eaten = false;
	weak = false;
	frozen = false;
}

void Ghosts::Ghost::Update(Level& level, float dt)
{
	float gameSpeedTick = speed * dt;
	gameSpeedTick = gameSpeedTick > 0.8f ? 0.8f : gameSpeedTick;

	bool isOpenLeft = false;
	bool isOpenRight = false;
	bool isOpenUp = false;
	bool isOpenDown = false;


	currentTime = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsedEatenDuration = currentTime - eatenTimeStart;
	float elapsedEatenTime = elapsedEatenDuration.count();

	if (eaten && (elapsedEatenTime >= eatenTimeMax))
	{
		eaten = false;
		weak = false;
	}


	else
	{

	}
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
		gameLoc.x = (float)(int)gameLoc.x + 0.000001f;
		isOpenUp = true;
	}
	if (direction.Equiv(DIRECTION::LEFT) && level.GetMapTileType(gameLoc + LL + DIRECTION::DOWN * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LR + DIRECTION::LEFT * gameSpeedTick + DIRECTION::DOWN * gameSpeedTick) < 4)
	{
		gameLoc.x = (float)(int)gameLoc.x + 0.000001f;
		isOpenDown = true;
	}

	bool movedAlreadyX = false;
	if (direction.Equiv(DIRECTION::RIGHT) && level.GetMapTileType(gameLoc + UR + DIRECTION::UP * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + UL + DIRECTION::RIGHT * gameSpeedTick + DIRECTION::UP * gameSpeedTick) < 4)
	{
		gameLoc.x = (float)(int)gameLoc.x + 1.000001f;
		movedAlreadyX = true;
		isOpenUp = true;
	}
	if (direction.Equiv(DIRECTION::RIGHT) && level.GetMapTileType(gameLoc + LR + DIRECTION::DOWN * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LL + DIRECTION::RIGHT * gameSpeedTick + DIRECTION::DOWN * gameSpeedTick) < 4)
	{
		if (!movedAlreadyX)
		{
			gameLoc.x = (float)(int)gameLoc.x + 1.000001f;
		}
		isOpenDown = true;
	}




	if (direction.Equiv(DIRECTION::UP) && level.GetMapTileType(gameLoc + UL + DIRECTION::LEFT * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LL + DIRECTION::UP * gameSpeedTick + DIRECTION::LEFT * gameSpeedTick) < 4)
	{
		gameLoc.y = (float)(int)gameLoc.y + 0.000001f;
		isOpenLeft = true;
	}
	if (direction.Equiv(DIRECTION::UP) && level.GetMapTileType(gameLoc + UR + DIRECTION::RIGHT * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + LR + DIRECTION::UP * gameSpeedTick + DIRECTION::RIGHT * gameSpeedTick) < 4)
	{
		gameLoc.y = (float)(int)gameLoc.y + 0.000001f;
		isOpenRight = true;
	}

	bool movedAlreadyY = false;
	if (direction.Equiv(DIRECTION::DOWN) && level.GetMapTileType(gameLoc + LL + DIRECTION::LEFT * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + UL + DIRECTION::DOWN * gameSpeedTick + DIRECTION::LEFT * gameSpeedTick) < 4)
	{
		gameLoc.y = (float)(int)gameLoc.y + 1.000001f;
		movedAlreadyY = true;
		isOpenLeft = true;
	}
	if (direction.Equiv(DIRECTION::DOWN) && level.GetMapTileType(gameLoc + LR + DIRECTION::RIGHT * gameSpeedTick) < 4 && level.GetMapTileType(gameLoc + UR + DIRECTION::DOWN * gameSpeedTick + DIRECTION::RIGHT * gameSpeedTick) < 4)
	{
		if (!movedAlreadyY)
		{
			gameLoc.y = (float)(int)gameLoc.y + 1.000001f;
		}
		isOpenRight = true;
	}


	if (direction.Equiv(DIRECTION::LEFT) && !isOpenLeft)
	{
		gameLoc.x = (float)(int)gameLoc.x + 0.000001f;
	}
	if (direction.Equiv(DIRECTION::RIGHT) && !isOpenRight)
	{
		gameLoc.x = (float)(int)gameLoc.x + 0.000001f;
	}
	if (direction.Equiv(DIRECTION::UP) && !isOpenUp)
	{
		gameLoc.y = (float)(int)gameLoc.y + 0.000001f;
	}
	if (direction.Equiv(DIRECTION::DOWN) && !isOpenDown)
	{
		gameLoc.y = (float)(int)gameLoc.y + 0.000001f;
	}

	if (!frozen)
	{
		ChooseDirection(isOpenLeft, isOpenRight, isOpenUp, isOpenDown);
	}

	if (!eaten)
	{
		gameLoc = gameLoc + direction * gameSpeedTick;

		TurnEyes(direction);
	}
}

void Ghosts::Ghost::ChooseDirection(bool isOpenLeft, bool isOpenRight, bool isOpenUp, bool isOpenDown)
{
	bool seenPacman = false;

	Vec2D pacmanUL = { -0.5f + 0.00001f, -0.5f + 0.00001f };
	Vec2D pacmanUR = { +0.5f - 0.00001f, -0.5f + 0.00001f };
	Vec2D pacmanLR = { +0.5f - 0.00001f, +0.5f - 0.00001f };
	Vec2D pacmanLL = { -0.5f + 0.00001f, +0.5f - 0.00001f };

	pacmanUL = pacmanGameLoc + pacmanUL;
	pacmanUR = pacmanGameLoc + pacmanUR;
	pacmanLR = pacmanGameLoc + pacmanLR;
	pacmanLL = pacmanGameLoc + pacmanLL;


	if ((isOpenLeft && (isOpenUp || isOpenDown || isOpenRight))
		|| (isOpenRight && (isOpenUp || isOpenDown || isOpenLeft))
		|| (isOpenUp && (isOpenLeft || isOpenRight || isOpenDown))
		|| (isOpenDown && (isOpenLeft || isOpenRight || isOpenUp)))
	{
		

		if (isOpenLeft && !(direction == DIRECTION::RIGHT))
		{
			for (int x = 1; x <= visionLength; x++)
			{
				if ((((int)pacmanUL.x == (int)gameLoc.x - x) || ((int)pacmanUR.x == (int)gameLoc.x - x) || ((int)pacmanLR.x == (int)gameLoc.x - x) || ((int)pacmanLL.x == (int)gameLoc.x - x))
					&& (((int)pacmanUL.y == (int)gameLoc.y) || ((int)pacmanUR.y == (int)gameLoc.y) || ((int)pacmanLR.y == (int)gameLoc.y) || ((int)pacmanLL.y == (int)gameLoc.y)))
				{
					direction = DIRECTION::LEFT;
					seenPacman = true;
				}
			}
		}
		if (isOpenRight && !(direction == DIRECTION::LEFT))
		{
			for (int x = 0; x <= visionLength; x++)
			{
				if ((((int)pacmanUL.x == (int)gameLoc.x + x) || ((int)pacmanUR.x == (int)gameLoc.x + x) || ((int)pacmanLR.x == (int)gameLoc.x + x) || ((int)pacmanLL.x == (int)gameLoc.x + x))
					&& (((int)pacmanUL.y == (int)gameLoc.y) || ((int)pacmanUR.y == (int)gameLoc.y) || ((int)pacmanLR.y == (int)gameLoc.y) || ((int)pacmanLL.y == (int)gameLoc.y)))
				{
					direction = DIRECTION::RIGHT;
					seenPacman = true;
				}
			}
		}
		if (isOpenUp && !(direction == DIRECTION::DOWN))
		{
			for (int y = 1; y <= visionLength; y++)
			{
				if ((((int)pacmanUL.y == (int)gameLoc.y - y) || ((int)pacmanUR.y == (int)gameLoc.y - y) || ((int)pacmanLR.y == (int)gameLoc.y - y) || ((int)pacmanLL.y == (int)gameLoc.y - y)) 
					&& (((int)pacmanUL.x == (int)gameLoc.x) || ((int)pacmanUR.x == (int)gameLoc.x) || ((int)pacmanLR.x == (int)gameLoc.x) || ((int)pacmanLL.x == (int)gameLoc.x)))
				{
					direction = DIRECTION::UP;
					seenPacman = true;
				}
			}
		}
		if (isOpenDown && !(direction == DIRECTION::UP))
		{
			for (int y = 1; y <= visionLength; y++)
			{
				if ((((int)pacmanUL.y == (int)gameLoc.y + y) || ((int)pacmanUR.y == (int)gameLoc.y + y) || ((int)pacmanLR.y == (int)gameLoc.y + y) || ((int)pacmanLL.y == (int)gameLoc.y + y))
					&& (((int)pacmanUL.x == (int)gameLoc.x) || ((int)pacmanUR.x == (int)gameLoc.x) || ((int)pacmanLR.x == (int)gameLoc.x) || ((int)pacmanLL.x == (int)gameLoc.x)))
				{
					direction = DIRECTION::DOWN;
					seenPacman = true;
				}
			}
		}
	}


	// choose random directions if can't see Pacman

	if (!seenPacman)
	{

		std::mt19937 rng(rd());

		std::uniform_int_distribution<int> directionRandGen2(1, 2);
		std::uniform_int_distribution<int> directionRandGen3(1, 3);
		std::uniform_int_distribution<int> directionRandGen4(1, 4);

		int directionRand2 = directionRandGen2(rng);
		int directionRand3 = directionRandGen3(rng);
		int directionRand4 = directionRandGen4(rng);


		if ((direction == DIRECTION::LEFT && isOpenLeft && !isOpenUp && !isOpenDown)
			|| (direction == DIRECTION::RIGHT && isOpenRight && !isOpenUp && !isOpenDown)
			|| (direction == DIRECTION::UP && isOpenUp && !isOpenLeft && !isOpenRight)
			|| (direction == DIRECTION::DOWN && isOpenDown && !isOpenLeft && !isOpenRight))
		{
			direction = direction;
		}
		else
		{
			if (direction == DIRECTION::LEFT)
			{
				if (isOpenLeft && isOpenUp && isOpenDown)
				{
					if (directionRand3 == 2)
					{
						direction = DIRECTION::UP;
					}
					else if (directionRand3 == 3)
					{
						direction = DIRECTION::DOWN;
					}
				}
				else if (isOpenLeft && isOpenUp)
				{
					if (directionRand2 == 2)
					{
						direction = DIRECTION::UP;
					}
				}
				else if (isOpenLeft && isOpenDown)
				{
					if (directionRand2 == 2)
					{
						direction = DIRECTION::DOWN;
					}
				}
				else if (isOpenUp && isOpenDown)
				{
					if (directionRand2 == 1)
					{
						direction = DIRECTION::DOWN;
					}
					else
					{
						direction = DIRECTION::UP;
					}
				}
				else if (isOpenUp)
				{
					direction = DIRECTION::UP;
				}
				else if (isOpenDown)
				{
					direction = DIRECTION::DOWN;
				}
			}

			else if (direction == DIRECTION::RIGHT)
			{
				if (isOpenRight && isOpenUp && isOpenDown)
				{
					if (directionRand3 == 2)
					{
						direction = DIRECTION::UP;
					}
					else if (directionRand3 == 3)
					{
						direction = DIRECTION::DOWN;
					}
				}
				else if (isOpenRight && isOpenUp)
				{
					if (directionRand2 == 2)
					{
						direction = DIRECTION::UP;
					}
				}
				else if (isOpenRight && isOpenDown)
				{
					if (directionRand2 == 2)
					{
						direction = DIRECTION::DOWN;
					}
				}
				else if (isOpenUp && isOpenDown)
				{
					if (directionRand2 == 1)
					{
						direction = DIRECTION::DOWN;
					}
					else
					{
						direction = DIRECTION::UP;
					}
				}
				else if (isOpenUp)
				{
					direction = DIRECTION::UP;
				}
				else if (isOpenDown)
				{
					direction = DIRECTION::DOWN;
				}
			}

			else if (direction == DIRECTION::UP)
			{
				if (isOpenUp && isOpenLeft && isOpenRight)
				{
					if (directionRand3 == 2)
					{
						direction = DIRECTION::LEFT;
					}
					else if (directionRand3 == 3)
					{
						direction = DIRECTION::RIGHT;
					}
				}
				else if (isOpenUp && isOpenLeft)
				{
					if (directionRand2 == 2)
					{
						direction = DIRECTION::LEFT;
					}
				}
				else if (isOpenUp && isOpenRight)
				{
					if (directionRand2 == 2)
					{
						direction = DIRECTION::RIGHT;
					}
				}
				else if (isOpenLeft && isOpenRight)
				{
					if (directionRand2 == 1)
					{
						direction = DIRECTION::RIGHT;
					}
					else
					{
						direction = DIRECTION::LEFT;
					}
				}
				else if (isOpenLeft)
				{
					direction = DIRECTION::LEFT;
				}
				else if (isOpenRight)
				{
					direction = DIRECTION::RIGHT;
				}
			}

			else if (direction == DIRECTION::DOWN)
			{
				if (isOpenDown && isOpenLeft && isOpenRight)
				{
					if (directionRand3 == 2)
					{
						direction = DIRECTION::LEFT;
					}
					else if (directionRand3 == 3)
					{
						direction = DIRECTION::RIGHT;
					}
				}
				else if (isOpenDown && isOpenLeft)
				{
					if (directionRand2 == 2)
					{
						direction = DIRECTION::LEFT;
					}
				}
				else if (isOpenDown && isOpenRight)
				{
					if (directionRand2 == 2)
					{
						direction = DIRECTION::RIGHT;
					}
				}
				else if (isOpenLeft && isOpenRight)
				{
					if (directionRand2 == 1)
					{
						direction = DIRECTION::RIGHT;
					}
					else
					{
						direction = DIRECTION::LEFT;
					}
				}
				else if (isOpenLeft)
				{
					direction = DIRECTION::LEFT;
				}
				else if (isOpenRight)
				{
					direction = DIRECTION::RIGHT;
				}
			}

		}

	}
}


Vec2D Ghosts::Ghost::GetGameLoc()
{
	return gameLoc;
}

Color Ghosts::Ghost::GetColor()
{
	if (!weak)
	{
		return c;
	}
	else
	{
		return weakColor;
	}
	
}

char Ghosts::Ghost::GetObjectMapState(int x, int y)
{
	if (eaten)
	{
		return objectMapEaten[y * 10 + x];
	}

	return objectMap[y * 10 + x];
}

char Ghosts::Ghost::GetEyeMapState(int x, int y)
{
	return eyeMap[y * 9 + x];
}

void Ghosts::Ghost::Freeze()
{
	direction = { 0.0f, 0.0f };
	frozen = true;
}

void Ghosts::Ghost::Unfreeze()
{
	frozen = false;
}

bool Ghosts::Ghost::IsEaten()
{
	return eaten;
}

bool Ghosts::Ghost::IsWeak()
{
	return weak;
}

void Ghosts::Ghost::SetEaten()
{
	eaten = true;
	weak = false;
	eatenTimeStart = std::chrono::system_clock::now();
	direction = DIRECTION::NONE;
	eatenSound.StopAll();
	eatenSound.Play(1.0f, 0.4f);

}

void Ghosts::Ghost::SetWeak()
{
	weak = true;

	Vec2D LEFT = { -1.0f, 0.0f };
	Vec2D RIGHT = { +1.0f, 0.0f };
	Vec2D UP = { 0.0f, -1.0f };
	Vec2D DOWN = { 0.0f, +1.0f };

	if (direction == LEFT)
	{
		direction = RIGHT;
	}
	else if (direction == RIGHT)
	{
		direction = LEFT;
	}
	else if (direction == UP)
	{
		direction = DOWN;
	}
	else if (direction == DOWN)
	{
		direction = UP;
	}

}

void Ghosts::Ghost::SetNotWeak()
{
	weak = false;
}

void Ghosts::Ghost::SetPacmanGameLoc(Vec2D in_loc)
{
	pacmanGameLoc = in_loc;
}

void Ghosts::Ghost::SetDirection(Vec2D in_direction)
{
	direction = in_direction;
}

void Ghosts::Ghost::TurnEyes(Vec2D in_direction)
{
	for (int i = 0; i < 81; i++)
	{
		if (in_direction.Equiv(DIRECTION::LEFT))
		{
			eyeMap[i] = eyeLeftMap[i];
		}
		if (in_direction.Equiv(DIRECTION::RIGHT))
		{
			eyeMap[i] = eyeRightMap[i];
		}
		if (in_direction.Equiv(DIRECTION::UP))
		{
			eyeMap[i] = eyeUpMap[i];
		}
		if (in_direction.Equiv(DIRECTION::DOWN))
		{
			eyeMap[i] = eyeDownMap[i];
		}
	}
}

void Ghosts::Ghost::InitStartScreen(Vec2D in_gameLoc, Color in_c, int number)
{
	gameLoc = in_gameLoc;
	initialised = true;
	c = in_c;
	direction = { 0.0f, 0.0f };
	frozen = false;

	TurnEyes(DIRECTION::UP);

}

void Ghosts::Ghost::UpdateStartScreen()
{



	if (gameLoc.x < 31.0f)
	{
		if (isGoingRightStartScreen)
		{
			gameLoc.x = gameLoc.x + 0.1f;
		}
		else
		{
			if (gameLoc.x > -6.0f)
			{
				gameLoc.x = gameLoc.x - 0.1f;
			}
			else
			{
				isGoingRightStartScreen = true;
				c = { (unsigned char)(255 - 50 * 0), (unsigned char)(0 + 50 * 0), (unsigned char)(200 - 30 * 2) };
				TurnEyes(DIRECTION::RIGHT);
				gameLoc.x = -6.0f + 0.01f;
			}
		}
		
	}
	else
	{
		isGoingRightStartScreen = false;
		c = Colors::Gray;
		gameLoc.x = 31.0f - 0.01f;
		TurnEyes(DIRECTION::LEFT);
	}


}

void Ghosts::Init()
{
	for (int i = 0; i < numGhosts; i++)
	{
		ghosts[i].Init({ (float)(11.0f + (float)i*1.5f), 11 }, { (unsigned char)(255 - 50 * i), (unsigned char)(0 + 50 * i), (unsigned char)(200 - 30 * i) }, i);
	}
	weakSound = Sound(L"AlienSiren.wav");
}

void Ghosts::Update(Level& level, float dt)
{
	currentTime = std::chrono::system_clock::now();

	std::chrono::duration<float> elapsedWeakTimeDuration = currentTime - globalWeakTimeStart;
	float elapsedWeakTime = elapsedWeakTimeDuration.count();

	if (globalWeak && (elapsedWeakTime >= globalWeakTimeMax))
	{
		globalWeak = false;
		for (int i = 0; i < numGhosts; i++)
		{
			ghosts[i].SetNotWeak();
		}
	}

	for (int i = 0; i < numGhosts; i++)
	{
		ghosts[i].Update(level, dt);
	}
}

void Ghosts::Freeze()
{
	for (int i = 0; i < numGhosts; i++)
	{
		ghosts[i].Freeze();
	}
}

void Ghosts::Unfreeze()
{
	for (int i = 0; i < numGhosts; i++)
	{
		ghosts[i].Unfreeze();
		ghosts[i].SetDirection(DIRECTION::LEFT);
	}
}

int Ghosts::GetNumber()
{
	return numGhosts;
}

char Ghosts::GetObjectMapState(int ghostNum, int x, int y)
{
	char state = ghosts[ghostNum].GetObjectMapState(x, y);
	return state;
}

char Ghosts::GetEyeMapState(int ghostNum, int x, int y)
{
	char state = ghosts[ghostNum].GetEyeMapState(x, y);
	return state;
}

Vec2D Ghosts::GetGameLoc(int i)
{
	return ghosts[i].GetGameLoc();
}

Color Ghosts::GetColor(int i)
{
	return ghosts[i].GetColor();
}

bool Ghosts::IsEaten(int i)
{
	return ghosts[i].IsEaten();
}

bool Ghosts::IsWeak(int i)
{
	globalWeak = true;
	return ghosts[i].IsWeak();
}

void Ghosts::SetEaten(int i)
{
	ghosts[i].SetEaten();
}

void Ghosts::SetWeak(int i)
{
	globalWeak = true;
	ghosts[i].SetWeak();
	weakSound.StopAll();
	weakSound.Play( 1.0f, 0.2f );
	globalWeakTimeStart = std::chrono::system_clock::now();
}

void Ghosts::SetPacmanGameLoc(Vec2D in_loc)
{
	for (int i = 0; i < numGhosts; i++)
	{
		ghosts[i].SetPacmanGameLoc(in_loc);
	}
}

void Ghosts::InitStartScreen()
{
	for (int i = 1; i < numGhosts; i++)
	{
		ghosts[i].InitStartScreen({ (float)(10.1f + (float)i*1.5f), 11 }, { (unsigned char)(255 - 50 * i), (unsigned char)(0 + 50 * i), (unsigned char)(200 - 30 * i) }, i);
	}

	ghosts[0].InitStartScreen({ 5.0f, 20.0f }, { (unsigned char)(255 - 50 * 0), (unsigned char)(0 + 50 * 0), (unsigned char)(200 - 30 * 2) }, 0);
	ghosts[0].TurnEyes(DIRECTION::RIGHT);
}

void Ghosts::UpdateStartScreen()
{
	ghosts[0].UpdateStartScreen();
}
