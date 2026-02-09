#pragma once
#include "CommonTypes.h"

class Combatant; // 전방선언: combatant가 공격 받은 상태를 받아 계산(반응)하기 위함.

class HitReactionStrategy
{
public:
	virtual ~HitReactionStrategy() = default;	 // 의문: default는 왜 하는가?

	// 판정하기 위해 필요한 Hit 정보들.
	virtual HitResult Execute(Combatant& owner, float timingDiff) = 0;

	// 패링 퀄리티 결과에 따라 효과 적용.
	void ApplyParryResult(Combatant* self, Combatant* target, ParryingQuality quality);
};

