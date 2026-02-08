#pragma once

#include "Common/Common.h"
#include <Windows.h>

namespace Wanted
{
	class WANTED_API Vector2
	{
	public:
		Vector2();
		Vector2(int x, int y);
		~Vector2();

		// 문자열로 변환해서 반환하는 함수.
		const char* ToString();

		// 연산자 오버로딩.
		Vector2 operator+(const Vector2& other) const;
		Vector2 operator-(const Vector2& other) const;

		bool operator==(const Vector2& other) const;
		bool operator!=(const Vector2& other) const;

		// 형변환 연산자 오버로딩.
		operator COORD() const;

		// 벡터 기본 값.
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Up;
		static Vector2 Right;


		// 방향벡터용 유클리드 함수 및 곱 연산자.
		void ChangeToUnitVector(); // 방향벡터에서 호출했을 때만 단위벡터가된다.
		Vector2 operator*(const int other) const;
		Vector2 operator*(const float other) const;
		Vector2& operator+=(const Vector2& other); // 스콧마이어스 표준 구현 형식

	public:
		// x/y 좌표.
		int x = 0;
		int y = 0;

	private:
		// 벡터 값을 문자열로 변환할 때 사용할 변수.
		char* string = nullptr;
	};
}
