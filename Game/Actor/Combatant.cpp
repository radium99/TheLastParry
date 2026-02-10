#include "Combatant.h"
#include "Level/Level.h"


Combatant::Combatant(const char* image, const Vector2& position, Color color, int currentPosture, int maxPosture, int maxHP, int currentHP)
	: super(image, position, color),
	maxPosture(maxPosture),
	currentPosture(currentPosture),
	maxHP(maxHP),
	currentHP(currentHP)
{
}

Combatant::~Combatant()
{
}


void Combatant::BeginPlay()
{
	super::BeginPlay();

	Vector2 progressPos = GetProgressBarPosition();
	// ProgressBar 생성 및 연결(값 전달).
	progressBar = new ProgressBar(currentPosture, maxPosture, progressPos);
	GetOwner()->AddNewActor(progressBar);

	Vector2 hpPos = GetHealthPointBarPosition();
	// ProgressBar 생성 및 연결(값 전달).
	healthPointBar = new HealthPointBar(currentHP, maxHP, hpPos);
	GetOwner()->AddNewActor(healthPointBar);
}


int Combatant::TakePostureDamage(int dmg)
{
	// 체간 데미지를 받았는데, 최대 체간 게이지를 넘을 경우.
	if (currentPosture + dmg >= maxPosture)
	{
		//postureBar.SetValue(currentPosture, maxPosture);
		// 전투 불능 상태 진입.
		IsPostureBroken(true);
		
		// 게이지 최대치를 넘지 않도록 방지.
		currentPosture = maxPosture;
	}
	else// 수용가능한 체간 데미지를 받은 경우.(체간 게이지 최대치를 넘지 않고)
	{
		currentPosture += dmg;
		IsPostureBroken(false);
	}

	// 체간 게이지바 표시 업데이트.
	progressBar->SetValue(currentPosture, maxPosture);
	
	return currentPosture;
}

int Combatant::TakeHealthPointDamage(int hpDmg)
{
	// 체력 데미지를 받았는데, 최소 체력 게이지를 넘을 경우.
	if (currentHP - hpDmg < 0)
	{
		// 게이지 최소치를 넘지 않도록 방지.
		currentHP = 0;
	}
	else// 수용가능한 체력 데미지를 받은 경우.(체력 게이지 최소치를 하회하지 않고)
	{
		currentHP -= hpDmg;
	}

	// 체간 게이지바 표시 업데이트.
	healthPointBar->SetValue(currentHP, maxHP);

	return currentHP;
}

int Combatant::TakeHealPoint(int heal)
{
	// 힐량이 넘칠 경우.
	if (currentHP + heal >= maxHP)
	{
		return  currentHP = maxHP;
	}
	
	// 힐량이 최대 범위를 넘지 않는 경우.
	return currentHP += heal;
}

int Combatant::GetCurrentHealthPoint()
{
	return currentHP;
}

void Combatant::IsPostureBroken(bool state)
{
	// 전투 불능인 경우.
	if (state)
	{
		// Todo: 전투 불능 상태로 변경 시키는 코드 작성.
	}
}

ParringStrategy* Combatant::parringStrategy(Combatant& owner, float timingDiff)
{	

	//Excute(*this);
	
	return nullptr;
}
