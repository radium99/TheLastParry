#include "HitReactionStrategy.h"
#include "Combatant.h"
#include "Actor/Enemy.h"

//HitResult HitReactionStrategy::Excute(Combatant& owner, const AttackInfo& attack, float timingDiff)
//{
//    return HitResult();
//}

void HitReactionStrategy::ApplyParryResult(Combatant* player, Enemy* enemy, ParryingQuality quality)
{
	switch (quality)
	{
	case ParryingQuality::Perfect:
		if (enemy)
		{
			enemy->OnDamaged(100, 100);
		}
		if (player)
		{
			player->TakeHealPoint(5);
		}
		break;

	case ParryingQuality::Great:
		if (enemy)
		{
			enemy->OnDamaged(60, 50);
		}
		if (player)
		{
			player->TakePostureDamage(5);
			player->TakeHealthPointDamage(5);
		}
		break;

	case ParryingQuality::Guard:
		if (enemy)
		{
			enemy->OnDamaged(40, 0);

		}
		if(player)
		{
			player->TakePostureDamage(10);
			player->TakeHealthPointDamage(10);
		}
		break;

	//case ParryingQuality::Fail:
	//	if (player)
	//	{
	//		player->TakePostureDamage(50);
	//		player->TakeHealthPointDamage(50);
	//	}
	//	break;

	}
}
