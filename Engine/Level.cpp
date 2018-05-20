#include "Level.h"

char* Level::GetCurrentMap()
{
	return p_map;
}

char Level::GetMapTileType(Vec2D gameLoc)
{
	return map[(int)((int)(gameLoc.y) * 28.0f) + (int)gameLoc.x];
}

void Level::SetMapTileType(Vec2D gameLoc, int type)
{
	map[(int)((int)(gameLoc.y) * 28.0f) + (int)gameLoc.x] = type;
}

int Level::GetLevel()
{
	return currentLevel;
}

