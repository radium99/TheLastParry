#pragma once
#include "Math/Vector2.h"	 // 위치 표현
#include "Math/Color.h"		// 체간 게이지 표현
#include <string>
#include "Engine/Engine.h"
#include "Actor/Actor.h"

using namespace Wanted;

// 전방 선언으로 클래스 포인터로 사용되어서 maxPosture와 currentPosture를 받을 예정. 아마도?
class ProgressBar : public Actor
{
	RTTI_DECLARATIONS(ProgressBar, Actor)

public:

	// 생성자.
	ProgressBar(
		int width = 10,
		char fill = 'F',
		char empty = 'E',
		Color fillColor = Color::White,
		Color emptyColor = Color::Blue,
		int sortingOrder = 5
	);

	// 소멸자.
	~ProgressBar();

	// Setter. private 내 접근하기 위한 함수.
	void SetValue(int current, int max);
	
	// 화면에 그리기(나타내기) 위한 함수.
	void Render();

private:
	virtual void Tick(float deltaTime) override;

	// 체간 수치를 저장하기 위한 변수.
	int _currentValue;
	int _maxValue;

	// 게이지바 위치 변수.
	//Vector2 _position;

	// 창에 표현하기 위한 게이지바 변수.
	int _width;
	char _fillChar;
	char _emptyChar;

	// 게이지바 색을 저장하는 변수.
	Color _fillColor;
	Color _emptyColor;

	int _sortingOrder;
};

