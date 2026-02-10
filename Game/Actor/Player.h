#pragma once

#include "Util/Timer.h"
#include "Actor/Combatant.h" // 0207  Actor -> Combatant로 상속 변경.
//#include "Actor/Progressbar.h"

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

	//virtual void BeginPlay() override; // BeginPlay 오버라이드 선언 추가 (ProgressBar 생성 및 Owner연결을 위함.)
	virtual void Tick(float deltaTime) override;

	// 마우스 위치로 이동하는 함수. 임경우.
	//void Move();


	// 오른쪽으로 이동하는 함수.
	//void MoveRight();
	
	// 왼쪽으로 이동하는 함수.
	//void MoveLeft();

	// 탄약 발사 함수.
	//void Fire(int dir);

	// 연속 발사 함수.
	//void FireInterval();

	// 발사 가능여부 확인 함수.
	bool CanShoot() const;


	// 테스트: 플레이어 위치 확인용 함수.
	//void ShowPos(Vector2& position);

	// 테스트: 플레이어 체간 확인용 함수.
	void ShowPosture();


	// 패링 확인 함수.
	bool IsParring() const { return isParring; }

	// 패링 중지 함수.
	void StopParry();

	// 패링 상태 변수.
	bool isParring = false;

	Vector2 GetProgressBarPosition() const override;
	Vector2 GetHealthPointBarPosition() const override;
private:

	// 패링 실행 함수.
	void StartParry(int dir);


	// 패링 지속 시간 변수: 패링 타이밍 측정을 위함.
	Timer parryTimer; // 의문: 패링 파일에 있어야 될 것 같다?

	// 패링 판정을 위한 시간 변수.
	float parryingDuration = 0.6f; // 의문: 패링 파일에 있어야 될 것 같다?


	// 발사 모드.
	FireMode fireMode = FireMode::None;

	// 타이머 변수.
	Timer timer;
	
	// 패링 쿨타임 변수.
	Timer coolTime;

	// 연사 시간 간격.
	//float parryingInterval = 0.2f;

	// 이동 속력.
	//float speed = 10.0f;

	// 체간 게이지를 위한 변수.
	//ProgressBar* playerProgressBar = nullptr;



};
