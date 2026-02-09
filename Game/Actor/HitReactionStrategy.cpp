#include "HitReactionStrategy.h"
#include "Combatant.h"

//HitResult HitReactionStrategy::Excute(Combatant& owner, const AttackInfo& attack, float timingDiff)
//{
//    return HitResult();
//}

void HitReactionStrategy::ApplyParryResult(Combatant* self, Combatant* target, ParryingQuality quality)
{
	switch (quality)
	{
	case ParryingQuality::Perfect:
		if (target)
		{
			target->TakePostureDamage(100);
		}
		break;

	case ParryingQuality::Great:
		if (target)
		{
			target->TakePostureDamage(60);
		}
		if (self)
		{
			self->TakePostureDamage(5);
		}
		break;

	case ParryingQuality::Guard:
		if (target)
		{
			target->TakePostureDamage(40);
		}
		if(self)
		{
		self->TakePostureDamage(10);
		}
		break;

	case ParryingQuality::Fail:
		if (self)
		{
			self->TakePostureDamage(50);
		}
		break;

	}
}
