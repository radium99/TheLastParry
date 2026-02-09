#pragma once
#include "Actor/Actor.h"
#include "CommonTypes.h"

//#include "Util/Timer.h" // 시간은 float로 받아서 계산만 하면 되기 때문에, 실제 Time을 알 필요없다.
using namespace Wanted;

class PlayerBullet;
class Combatant;

class ParryingStrategy : public Actor
{
	RTTI_DECLARATIONS(ParryingStrategy, Actor)

public:

    // #define보다 const, enum, inline을 우선하자

    //struct PostureConstants {
    //    static constexpr float MAX_POSTURE = 100.0f;
    //    static constexpr float RECOVERY_BASE = 5.0f;
    //    static constexpr float PERFECT_WINDOW = 0.12f; // 초 단위
    //};

    //HitResult Excute(Combatant& combatant, const float timingDiff);

    ParryingQuality CalculateParryQuality(float elapsedTime);

private:

    
};

