#include "Vector2.h"
#include <iostream>

namespace Wanted
{
	Vector2 Vector2::Zero(0, 0);
	Vector2 Vector2::One(1, 1);
	Vector2 Vector2::Up(0, 1);
	Vector2 Vector2::Right(1, 0);

	Vector2::Vector2()
	{
	}

	Vector2::Vector2(int x, int y)
		: x(x), y(y)
	{
	}
	
	Vector2::~Vector2()
	{
		if (string)
		{
			delete[] string;
			string = nullptr;
		}
	}
	
	const char* Vector2::ToString()
	{

		// 기존 문자열이 있다면 제거.
		if (string)
		{
			delete[] string;
			string = nullptr;
		}

		string = new char[128];
		memset(string, 0, sizeof(char) * 128);
		sprintf_s(string, 128, "(%f, %f)", x, y);

		return string;
	}

	Vector2 Vector2::operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 Vector2::operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	bool Vector2::operator==(const Vector2& other) const
	{
		return (x == other.x) && (y == other.y);
	}

	bool Vector2::operator!=(const Vector2& other) const
	{
		return !(*this == other);
	}

	Vector2::operator COORD() const
	{
		COORD coord = {};
		coord.X = static_cast<short>(x);
		coord.Y = static_cast<short>(y);

		return coord;
	}
	
	//void Vector2::ChangeToUnitVector()
	//{
	//	// 아래 두 녀석을 float로 받으면 플레이억 좌우로 흔들림.
	//	float distanceSquare = x*x + y*y;	// 방향벡터 타겟(x, y), 플레이어(a,b)  => (x-a)^2, (y - b)^2
	//	float len = sqrtf(distanceSquare); // 거리구함.

	//	if (len != 0.0f)
	//	{
	//		x =	x / len;
	//		y =	y / len;
	//	}
	//}
	Vector2 Vector2::operator*(const int other) const
	{
		return Vector2(x * other, y* other);
	}

	Vector2 Vector2::operator*(const float other) const
	{
		return Vector2(x * other, y * other);
	}

	Vector2& Vector2::operator+=(const Vector2& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}
}