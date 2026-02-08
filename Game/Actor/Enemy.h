#pragma once

#include "Util/Timer.h"
#include "Actor/Combatant.h" // 0207  Actor -> Combatant로 상속 변경.

using namespace Wanted;

class Enemy : public Combatant
{
	RTTI_DECLARATIONS(Enemy, Combatant)

	// 이동 방향 열거형.
	enum class MoveDirection
	{
		None = -1,
		Left,
		Right
	};

public:
	Enemy(const char* image = "(oOo)", int yPosition = 5);
	~Enemy();

	// Tick.
	virtual void Tick(float deltaTime) override;

	// 대미지 받았을 때 처리할 함수.
	void OnDamaged(int dmg);

private:
	// 이동 방향 열거형.
	MoveDirection direction = MoveDirection::None;

	// 좌우 이동 처리를 위한 변수.
	float xPosition = 0.0f;
	float moveSpeed = 5.0f;

	// 발사 타이머.
	Timer timer;
};
