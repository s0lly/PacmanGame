#pragma once

struct Vec2D
{

public:
	float x;
	float y;

	void operator+=(const Vec2D rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}
	Vec2D operator+(const Vec2D rhs)
	{
		return { x + rhs.x, y + rhs.y };
	}
	bool operator==(const Vec2D rhs)
	{
		if (x == rhs.x && y == rhs.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void operator*=(const Vec2D rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
	}
	Vec2D operator*(const Vec2D rhs) const
	{
		return { x * rhs.x, y * rhs.y };
	}
	Vec2D operator*(const float rhs) const
	{
		return { x * rhs, y * rhs };
	}

	bool Equiv(Vec2D rhs)
	{
		if (x > rhs.x - 0.00001f && x < rhs.x + 0.00001f && y > rhs.y - 0.00001f && y < rhs.y + 0.00001f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

private:


};

namespace DIRECTION
{
	static constexpr Vec2D LEFT		= { -1.0f, +0.0f };
	static constexpr Vec2D RIGHT	= { +1.0f, +0.0f };
	static constexpr Vec2D UP		= { +0.0f, -1.0f };
	static constexpr Vec2D DOWN		= { +0.0f, +1.0f };
	static constexpr Vec2D NONE		= { +0.0f, +0.0f };
}