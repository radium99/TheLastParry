#include "ParringStrategy.h"

//HitResult ParryingStrategy::Excute(Combatant& combatant, const AttackInfo& attackInfo, const float timingDiff)
//{
//    HitResult result;
//    if (timingDiff <= 0.2f)
//    {
//        result.parryingQuality = ParryingQuality::Perfect;
//    }
//    else if (timingDiff <= 0.5f)
//    {
//        result.parryingQuality = ParryingQuality::Great;
//    }
//    else
//    {
//        result.parryingQuality = ParryingQuality::Guard;
//    }
//
//    switch (result.parryingQuality)
//    {
//    case ParryingQuality::Perfect:
//        result.damage = 0;
//        result.postureDamage = 0;
//        //if (attackInfo.attacker != nullptr)
//        //{
//        //    // const 포인터이므로 멤버 함수로 수정 필요
//        //    // Combatant에 currentPosture를 변경하는 public 멤버 함수가 있다고 가정
//        //    // 예: TakePostureDamage(int dmg)
//        //    attackInfo.attacker->TakePostureDamage(attackInfo.postureDamage);
//        //}
//        break;
//
//    case ParryingQuality::Great:
//        result.damage = 0;
//        result.postureDamage = 10;
//        break;
//
//    case ParryingQuality::Guard:
//        result.damage = 0;
//        result.postureDamage = 20;
//        break;
//
//    //default:
//    //  break;
//    }
//
//    return result;
//}

ParryingQuality ParryingStrategy::CalculateParryQuality(float elapsedTime)
{
    if (elapsedTime <= 0.2f)
    {
        return ParryingQuality::Perfect;
    }
    else if (elapsedTime <= 0.5f)
    {
        return ParryingQuality::Great;
    }
    else
    {
        return ParryingQuality::Guard;
    }

}
