#pragma once
#include "Math/Vector2.h"	 // 위치 표현
#include "Math/Color.h"		// 체간 게이지 표현
#include <string>
#include "Engine/Engine.h"
#include "Actor/Actor.h"
#include "Util/Timer.h"

using namespace Wanted;

// 전방 선언으로 클래스 포인터로 사용되어서 maxPosture와 currentPosture를 받을 예정. 아마도?
class HealthPointBar : public Actor
{
	RTTI_DECLARATIONS(HealthPointBar, Actor)

public:

	// 생성자.
	HealthPointBar(int currentValue, int maxValue, Vector2& position);

	// 소멸자.
	~HealthPointBar();

	// Setter. private 내 접근하기 위한 함수.
	void SetValue(int current, int max);

	virtual void Tick(float deltaTime) override;

private:


	// 이미지 교체를 위한 변수.
	const char* image;

	// 체간 수치를 저장하기 위한 변수.
	int _currentValue;
	int _maxValue;

	// 게이지바 위치 변수.
	//Vector2 _position;

	// 창에 표현하기 위한 게이지바 변수.
	//int _width;
	//char _fillChar;
	//char _emptyChar;

	// 게이지바 색을 저장하는 변수.
	//Color _fillColor;
	//Color _emptyColor;

	int _sortingOrder = 11;

	// 생성 타이머.
	Timer timer;
};

