#pragma once

#include "Vec2D.h"
#include "Keyboard.h"
#include "Colors.h"
#include "Level.h"
#include "Ghosts.h"
#include "Sound.h"
#include <chrono>


class Pacman
{
public:
	void Init();

	void Update(Keyboard& kbd, Level& level, Ghosts& ghosts, float dt, Sound& eatingSound);
	void CheckCollisionWalls(Level& level, float dt);
	void CheckEatingPellet(Level& level, Sound& eatingSound);
	void CheckEatingPowerup(Level& level, Ghosts& ghosts);
	void StartPowerupMode(Ghosts& ghosts);
	void CheckCollisionGhosts(Ghosts& ghosts);
	void LoseLife(Ghosts& ghosts);
	int GetLives();
	bool isLifeLost();

	Vec2D GetGameLoc();
	Color GetColor();

	bool IsMouthOpen();

	Vec2D GetDirection();

	int GetScore();

	void InitStartScreen();
	void UpdateStartScreen();

	float GetScale();

private:
	Vec2D startLoc = { 14.0f, 23.5f };
	Vec2D gameLoc = startLoc;
	Vec2D direction = { 0.0f, 0.0f };
	const float speed = 6.0f;

	Vec2D moveBuffer = { 0.0f, 0.0f };

	Color c = Colors::Yellow;
	bool isLeftPressed = false;
	bool isRightPressed = false;
	bool isUpPressed = false;
	bool isDownPressed = false;

	bool poweredUp = false;
	float poweredUpTimerMax = 10.0f;
	float poweredUpTimerCurrent = 0.0f;
	float poweredUpTimerTick = 0.1f;

	int lives = 2;
	bool lifeLostState = false;
	float lifeLostStateTimerMax = 10.0f;
	float lifeLostStateTimerCurrent = 0.0f;
	float lifeLostStateTimerTick = 0.1f;

	bool initilising = true;
	float initStateTimerMax = 3.0f;
	float initStateTimerCurrent = 0.0f;
	float initStateTimerTick = 0.1f;

	Vec2D UL = { -0.5f + 0.00001f, -0.5f + 0.00001f };
	Vec2D UR = { +0.5f - 0.00001f, -0.5f + 0.00001f };
	Vec2D LR = { +0.5f - 0.00001f, +0.5f - 0.00001f };
	Vec2D LL = { -0.5f + 0.00001f, +0.5f - 0.00001f };

	bool mouthOpen = true;

	int score = 0;
	int scoreLife = 0;
	int scoreLifeUp = 1000;

	bool isGoingRightStartScreen = true;
	
	float scale = 1.0f;

};