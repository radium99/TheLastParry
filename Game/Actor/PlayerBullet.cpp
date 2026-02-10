#include "PlayerBullet.h"

PlayerBullet::PlayerBullet(const Vector2& position)
	: super("*", position, Color::Yellow),
	yPosition(static_cast<float>(position.y))
{
	timer.SetTargetTime(lifeTime); // 패링 최대 지속 시간 설정.
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
		// 패링 최대 지속 시간 도달 시 삭제 처리.
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
