#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"

#include "Actor/HitReactionStrategy.h"
#include "Actor/ParringStrategy.h"
//#include <memory>

using namespace Wanted;

class PlayerBullet;
class Player;
class Enemy;
class ParryingStrategy;
class HitReactionStrategy;

class GameLevel : public Level
{
	// RTTI 등록.
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel();
	~GameLevel();

	// 패링 판정 관련 함수.

    // 기존 선언에서 Player* 타입이 일치하지 않아 발생하는 오류를 수정합니다.
    // 아래와 같이 함수 선언을 명확히 Player* 타입으로 맞춰줍니다.

    void ProcessParry(PlayerBullet* parryObject, Enemy* enemy, Player* player);
private:

	// 패링 판정 관련 전략 객체들 변수 선언.
	ParryingStrategy* parryingStrategy;
	HitReactionStrategy* hitReactionStrategy;

	//std::unique_ptr<ParringQuality> parryingStrategy = std::make_unique<ParringQuality>;

	virtual void Tick(float deltaTime) override;
	virtual void Draw() override;

	// 충돌 판정 처리 함수.
	void ProcessCollisionParryingAndEnemy();
	void ProcessCollisionEnemyAndPlayer();

	// 점수 보여주는 함수.
	void ShowScore();

private:
	// 점수 변수.
	int score = 0;

	// 플레이어가 죽었는지 확인.
	bool isPlayerDead = false;

	// 플레이어가 죽은 위치 (Draw에서 처리하기 위해 Tick에서 저장).
	Vector2 playerDeadPosition;

	// 점수 문자열.
	char scoreString[128] = {};
};
