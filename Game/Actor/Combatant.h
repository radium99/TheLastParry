#pragma once
#include "Actor/Actor.h"
#include "Actor/Progressbar.h"
#include "Actor/HealthPointBar.h"

using namespace Wanted;

class ParringStrategy; // 전방 선언: 참조순환 및 컴파일 시간 단축을 위함.
class ParringQuality;
class HitReactionStrategy;

class Combatant : public Actor
{
	RTTI_DECLARATIONS(Combatant, Actor)

public:
	virtual void BeginPlay() override; // BeginPlay 오버라이드 선언 추가 (ProgressBar 생성 및 Owner연결을 위함.)

	// 생성자."*(oo)*", Vector2::Zero, Color::Green
	Combatant(
		const char* image = "",
		const Vector2& position = Vector2::Zero,
		Color color = Color::White,
		int currentPosture = 0,
		int maxPosture = 100,
		int maxHP = 0,
		int currentHP = 0);

	virtual ~Combatant();
	
	// 받은 체간 데미지 업데이트를 위한 함수.
	int TakePostureDamage(int dmg);


	// 전투 불능 상태 확인하는 함수.
	void IsPostureBroken(bool state);

	//패링 시스템 함수.
	ParringStrategy* parringStrategy(Combatant& owner,  float timingDiff);

	// 받은 체력 데미지 업데이트를 위한 함수.
	int TakeHealthPointDamage(int hpDmg);
	
	int GetCurrentHealthPoint();

	int TakeHealPoint(int heal);

protected:

	// 체간 최대치.
	int maxPosture = 100;

	// 현재 체간 수치.
	int currentPosture = 0;

	// 전툭 가능 상태여부 변수.
	bool isCombatable = true;
	// 체간 게이지를 위한 변수.
	ProgressBar* progressBar = nullptr;

	HealthPointBar* healthPointBar = nullptr;

	// Progress바 위치 제공 함수.
	virtual Vector2 GetProgressBarPosition() const { return Vector2::Zero; }
	
	// 체력 관련 변수.
	int maxHP = 100;
	int currentHP = 100;
	
	// HealthPoint바 위치 제공 함수.
	virtual Vector2 GetHealthPointBarPosition() const { return Vector2::Zero; }
};

