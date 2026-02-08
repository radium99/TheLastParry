#include "Combatant.h"


Combatant::Combatant(const char* image, const Vector2& position, Color color, int currentPosture, int maxPosture)
	: super(image, position, color),
	maxPosture(maxPosture),
	currentPosture(currentPosture)
{
}

Combatant::~Combatant()
{
}

int Combatant::TakePostureDamage(int dmg)
{
	// 체간 데미지를 받았는데, 최대 체간 게이지를 넘을 경우.
	if (currentPosture + dmg >= maxPosture)
	{
		postureBar.SetValue(currentPosture, maxPosture);
		postureBar.Render();
		// 전투 불능 상태 진입.
		IsPostureBroken(true);
		
		// 게이지 최대치를 넘지 않도록 방지.
		return currentPosture = maxPosture;
	}
	postureBar.SetValue(currentPosture, maxPosture);
	postureBar.Render();       

	return currentPosture += dmg;
	// 수용가능한 체간 데미지를 받은 경우.(체간 게이지 최대치를 넘지 않고)
}

void Combatant::IsPostureBroken(bool state)
{
	// 전투 불능인 경우.
	if (state)
	{
		// Todo: 전투 불능 상태로 변경 시키는 코드 작성.
	}
}

void Combatant::Render() {
	postureBar.Render();
}