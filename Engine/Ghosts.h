#pragma once

#include "Vec2D.h"
#include "Colors.h"
#include "Level.h"
#include "Sound.h"
#include <random>
#include <chrono>


class Ghosts
{
private:

	class Ghost
	{
	public:
		void Init(Vec2D in_gameLoc, Color in_c, int number);

		void Update(Level& level, float dt);

		void ChooseDirection(bool isOpenLeft, bool isOpenRight, bool isOpenUp, bool isOpenDown);

		Vec2D GetGameLoc();
		Color GetColor();

		char GetObjectMapState(int x, int y);
		char GetEyeMapState(int x, int y);

		void Freeze();
		void Unfreeze();

		bool IsEaten();
		bool IsWeak();

		void SetEaten();
		void SetWeak();
		void SetNotWeak();

		void SetPacmanGameLoc(Vec2D in_loc);
		void SetDirection(Vec2D in_direction);
		void TurnEyes(Vec2D direction);

		void InitStartScreen(Vec2D in_gameLoc, Color in_c, int number);
		void UpdateStartScreen();

	private:

		Vec2D gameLoc = { 0.0f, 0.0f };
		Vec2D direction = { 0.0f, 0.0f };
		const float speed = 6.0f;

		bool initialised = false;
		Color c = Colors::Green;

		Vec2D UL = { 0.0f + 0.00001f, 0.0f + 0.00001f };
		Vec2D UR = { 1.0f - 0.00001f, 0.0f + 0.00001f };
		Vec2D LR = { 1.0f - 0.00001f, 1.0f - 0.00001f };
		Vec2D LL = { 0.0f + 0.00001f, 1.0f - 0.00001f };

		std::chrono::system_clock::time_point currentTime;

		std::chrono::system_clock::time_point eatenTimeStart;
		const float eatenTimeMax = 4.0f;

		bool eaten = false;

		Vec2D pacmanGameLoc;

		float targetLength = 4.0f;

		bool weak = false;

		Color weakColor = Colors::LightGray;

		bool frozen = false;

		int visionLength = 6;

		char objectMap[100] =
		{
			0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
			0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
			0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 0, 1, 1, 1, 1, 0, 1, 1,
			0, 1, 0, 0, 1, 1, 0, 0, 1, 0
		};

		char objectMapEaten[100] =
		{
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0
		};

		char* p_objectMap;

		std::random_device rd;
		std::mt19937 rng;

		char eyeMap[81] = { 0 };

		char eyeLeftMap[81] =
		{
			0, 0, 1, 1, 1, 1, 1, 0, 0,
			0, 0, 1, 1, 1, 1, 1, 0, 0,
			2, 2, 2, 2, 2, 1, 1, 1, 1,
			2, 2, 2, 2, 2, 1, 1, 1, 1,
			2, 2, 2, 2, 2, 1, 1, 1, 1,
			2, 2, 2, 2, 2, 1, 1, 1, 1,
			2, 2, 2, 2, 2, 1, 1, 1, 1,
			0, 0, 1, 1, 1, 1, 1, 0, 0,
			0, 0, 1, 1, 1, 1, 1, 0, 0
		};
		char eyeRightMap[81] =
		{
			0, 0, 1, 1, 1, 1, 1, 0, 0,
			0, 0, 1, 1, 1, 1, 1, 0, 0,
			1, 1, 1, 1, 2, 2, 2, 2, 2,
			1, 1, 1, 1, 2, 2, 2, 2, 2,
			1, 1, 1, 1, 2, 2, 2, 2, 2,
			1, 1, 1, 1, 2, 2, 2, 2, 2,
			1, 1, 1, 1, 2, 2, 2, 2, 2,
			0, 0, 1, 1, 1, 1, 1, 0, 0,
			0, 0, 1, 1, 1, 1, 1, 0, 0
		};
		char eyeUpMap[81] =
		{
			0, 0, 2, 2, 2, 2, 2, 0, 0,
			0, 0, 2, 2, 2, 2, 2, 0, 0,
			1, 1, 2, 2, 2, 2, 2, 1, 1,
			1, 1, 2, 2, 2, 2, 2, 1, 1,
			1, 1, 2, 2, 2, 2, 2, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1,
			0, 0, 1, 1, 1, 1, 1, 0, 0,
			0, 0, 1, 1, 1, 1, 1, 0, 0
		};
		char eyeDownMap[81] =
		{
			0, 0, 1, 1, 1, 1, 1, 0, 0,
			0, 0, 1, 1, 1, 1, 1, 0, 0,
			1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 1, 1, 1, 1, 1, 1, 1,
			1, 1, 2, 2, 2, 2, 2, 1, 1,
			1, 1, 2, 2, 2, 2, 2, 1, 1,
			1, 1, 2, 2, 2, 2, 2, 1, 1,
			0, 0, 2, 2, 2, 2, 2, 0, 0,
			0, 0, 2, 2, 2, 2, 2, 0, 0
		};

		Sound eatenSound;

		bool isGoingRightStartScreen = true;
	};

public:
	
	void Init();

	void Update(Level& level, float dt);

	void Freeze();
	void Unfreeze();

	int GetNumber();
	char GetObjectMapState(int ghostNum, int x, int y);
	char GetEyeMapState(int ghostNum, int x, int y);
	Vec2D GetGameLoc(int i);
	Color GetColor(int i);

	bool IsEaten(int i);
	bool IsWeak(int i);

	void SetEaten(int i);
	void SetWeak(int i);

	void SetPacmanGameLoc(Vec2D in_loc);

	void InitStartScreen();

	void UpdateStartScreen();


private:
	static constexpr int numGhosts = 5;
	Ghost ghosts[numGhosts];

	std::chrono::system_clock::time_point currentTime;

	bool globalWeak = false;
	std::chrono::system_clock::time_point globalWeakTimeStart;
	const float globalWeakTimeMax = 6.5f;

	Sound weakSound;

};