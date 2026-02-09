#pragma once

#include "Util/Timer.h"
#include "Actor/Combatant.h" // 0207  Actor -> Combatant로 상속 변경.
#include "Actor/Progressbar.h"

using namespace Wanted;

class Player : public Combatant
{
	// 발사 모드.
	enum class FireMode
	{
		None = -1,
		OneShot,
		Repeat
	};

	RTTI_DECLARATIONS(Player, Combatant)

public:
	Player();
	~Player();

private:

	virtual void BeginPlay() override; // BeginPlay 오버라이드 선언 추가
	virtual void Tick(float deltaTime) override;

	// 마우스 위치로 이동하는 함수. 임경우.
	void Move();


	// 오른쪽으로 이동하는 함수.
	void MoveRight();
	
	// 왼쪽으로 이동하는 함수.
	void MoveLeft();

	// 탄약 발사 함수.
	void Fire(int dir);

	// 연속 발사 함수.
	void FireInterval();

	// 발사 가능여부 확인 함수.
	bool CanShoot() const;


	// 테스트: 플레이어 위치 확인용 함수.
	void ShowPos(Vector2& position);

	// 테스트: 플레이어 체간 확인용 함수.
	void ShowPosture();

	// Progress바 생성.
	//void AddPlayerProgressBar();

	// 플레이어 페링 지속 시간 함수.
	void ParryingTime();

private:
	// 발사 모드.
	FireMode fireMode = FireMode::None;

	// 타이머 변수.
	Timer timer;
	
	// 연사 시간 간격.
	float fireInterval = 0.2f;

	// 이동 속력.
	float speed = 10.0f;

	ProgressBar* playerProgressBar = nullptr;
};
