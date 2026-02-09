#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const Vector2& position)
	: super("@", position, Color::Blue),
	yPosition(static_cast<float>(position.y))
{
	timer.SetTargetTime(lifeTime); // 60프레임 기준. 1초?
	timer.Reset();
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	// 좌표 검사.
	timer.Tick(deltaTime);
	if (timer.IsTimeOut()) { // yPosition < 0.0f
		// 삭제 처리.
		Destroy();
		return;
	}

	// 위로 이동 처리. 초단위로 이동.
	//yPosition -= moveSpeed * deltaTime;

	// 경과 시간 업데이트.
	//timer.Tick(deltaTime);
	//if (!timer.IsTimeOut())
	//{
	//	return;
	//}
	//timer.Reset();
	

	// 액터의 위치로 변환.
	Vector2 newPosition = GetPosition();
	newPosition.y = static_cast<int>(yPosition);
	
	// 위치 갱신.
	SetPosition(newPosition);
}
