#pragma once
#include "Actor/Actor.h"
#include "Actor/Progressbar.h"


using namespace Wanted;

class ParringStrategy; // 전방 선언: 참조순환 및 컴파일 시간 단축을 위함.
class ParringQuality;
class HitReactionStrategy;

class Combatant : public Actor
{
	RTTI_DECLARATIONS(Combatant, Actor)

public:

	// 생성자."*(oo)*", Vector2::Zero, Color::Green
	Combatant(
		const char* image = "",
		const Vector2& position = Vector2::Zero,
		Color color = Color::White,
		int currentPosture = 0,
		int maxPosture = 100);

	virtual ~Combatant();
	
	// 받은 체간 데미지 업데이트를 위한 함수.
	int TakePostureDamage(int dmg);


	// 전투 불능 상태 확인하는 함수.
	void IsPostureBroken(bool state);

	//패링 시스템 함수.
	ParringStrategy* parringStrategy(Combatant& owner,  float timingDiff);
	
protected:

	// 체간 최대치.
	int maxPosture = 100;

	// 현재 체간 수치.
	int currentPosture = 0;
};

