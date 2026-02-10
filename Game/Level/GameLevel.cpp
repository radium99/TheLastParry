#include "GameLevel.h"
#include "Actor/Player.h"
#include "Actor/Enemy.h"
#include "Actor/PlayerBullet.h"
#include "Actor/EnemyBullet.h"
#include "Actor/EnemySpawner.h"
#include "Actor/MouseTester.h"
#include "Render/Renderer.h"
#include "Engine/Engine.h"
#include "Actor/Progressbar.h"

GameLevel::GameLevel()
{
	// Player 액터 추가.
	AddNewActor(new Player());

	// 적 생성기 추가.
	AddNewActor(new EnemySpawner());

	// Test: 마우스 테스터 추가.
	AddNewActor(new MouseTester());

	// Test: 체간 게이지 표시 추가.
	//AddNewActor(new ProgressBar());

}

GameLevel::~GameLevel()
{
	delete parryingStrategy;
	parryingStrategy = nullptr;
}

void GameLevel::ProcessParry(PlayerBullet* parryObject, Enemy* enemy, Player* player)
{
	if (!parryObject || !enemy || !player)
	{
		return;
	}
	// 패링 지속 시간 받아오기
	float elapsedTime = parryObject->GetParryingElapsedTime(); 

	// 받은 시간을 기반으로 패링 퀄리티 계산.
	ParryingQuality quality = parryingStrategy->CalculateParryQuality(elapsedTime);

	if (player)
	{
		hitReactionStrategy->ApplyParryResult(player, enemy, quality);
	}
}

void GameLevel::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 충돌 판정 처리.
	ProcessCollisionParryingAndEnemy(); // 패링오브젝트 & Enemy
	ProcessCollisionEnemyAndPlayer();	// 플레이어 &  Enemy
	//ProcessCollisionEnemyAndPlayer();
	
	//ProcessCollisionPlayerBulletAndEnemy();
	//ProcessCollisionPlayerAndEnemyBullet();
}

void GameLevel::Draw()
{
	super::Draw();

	if (isPlayerDead)
	{
		// 플레이어 죽음 메시지 Renderer에 제출.
		Renderer::Get().Submit("!Dead!", playerDeadPosition);

		// 점수 보여주기.
		ShowScore();

		// 화면에 바로 표시.
		Renderer::Get().PresentImmediately();

		// 프로그램 정지.
		Sleep(2000);

		// 게임 종료.
		Engine::Get().QuitEngine();
	}

	// 점수 보여주기.
	ShowScore();
}

// 패링오브젝트와 Enemy 충돌 처리.
void GameLevel::ProcessCollisionParryingAndEnemy()
{
	// 플레이어 탄약과 적 액터 필터링.
	std::vector<PlayerBullet*> parryings;
	std::vector<Enemy*> enemies;
	Player* player = nullptr; // Player*로 선언

	// 액터 필터링.
	for (Actor* const actor : actors)
	{
		if (actor->IsTypeOf<PlayerBullet>())
		{
			parryings.emplace_back(actor->As<PlayerBullet>());
			continue;
		}

		if (actor->IsTypeOf<Enemy>())
		{
			enemies.emplace_back(actor->As<Enemy>());
		}

		if (!player && actor->IsTypeOf<Player>())
		{
			player = actor->As<Player>(); // 타입 변환
		}
	}

	// 판정 안해도 되는지 확인.
	if (parryings.size() == 0 || enemies.size() == 0)
	{
		return;
	}

	// 충돌 판정.
	for (PlayerBullet* const parrying : parryings)
	{
		for (Enemy* const enemy : enemies)
		{
			// AABB 겹침 판정.
			if (parrying->TestIntersect(enemy))
			{
				ProcessParry(parrying, enemy, player);
				//enemy->OnDamaged(100); // 기존 enemy->OnDamaged();

				// 페링 시스템을 넣었다면(Perfect, good, bad) 페링모션 자체는 없어지면 안될 것 같다고 판단.
				//parry->Destroy();

				// 점수 추가.
				score += 1;
				continue;
			}
		}
	}
}
//void GameLevel::ProcessCollisionEnemyHitPlayer()
//{
//	// 플레이어 탄약과 적 액터 필터링.
//	std::vector<Actor*> bullets;
//	std::vector<Enemy*> enemies;
//
//	// 액터 필터링.
//	for (Actor* const actor : actors)
//	{
//		if (actor->IsTypeOf<PlayerBullet>())
//		{
//			bullets.emplace_back(actor);
//			continue;
//		}
//
//		if (actor->IsTypeOf<Enemy>())
//		{
//			enemies.emplace_back(actor->As<Enemy>());
//		}
//	}
//
//	// 판정 안해도 되는지 확인.
//	if (bullets.size() == 0 || enemies.size() == 0)
//	{
//		return;
//	}
//
//	// 충돌 판정.
//	for (Actor* const bullet : bullets)
//	{
//		for (Enemy* const enemy : enemies)
//		{
//			// AABB 겹침 판정.
//			if (bullet->TestIntersect(enemy))
//			{
//				enemy->OnDamaged(10); // 기존 enemy->OnDamaged();
//				bullet->Destroy();
//
//				// 점수 추가.
//				score += 1;
//				continue;
//			}
//		}
//	}
//}

// 플레이어와 Enemy 충돌 처리: 패링 실패 or 피격 시
void GameLevel::ProcessCollisionEnemyAndPlayer()
{
	// 액터 필터링을 위한 변수.
	Player* player = nullptr;
	std::vector<Actor*> enemys;

	// 액터 필터링.
	for (Actor* const actor : actors)
	{
		if (!player && actor->IsTypeOf<Player>())
		{
			player = actor->As<Player>();
			continue;
		}

		if (actor->IsTypeOf<Enemy>())
		{
			enemys.emplace_back(actor);
		}
	}

	// 판정 처리 안해도 되는지 확인.
	if (enemys.size() == 0 || !player)
	{
		return;
	}

	// 충돌 판정.
	for (Actor* const enemy : enemys)
	{
		if (enemy->TestIntersect(player))
		{
			enemy->Destroy();
			player->TakeHealthPointDamage(50);

			if (player->GetCurrentHealthPoint() <= 0)
			{
				// 플레이어 죽음 설정.
				isPlayerDead = true;

				// 죽은 위치 저장.
				playerDeadPosition = player->GetPosition();

				// 액터 제거 처리.
				player->Destroy();
			}

			break;
		}
	}
}

void GameLevel::ShowScore()
{
	sprintf_s(scoreString, 128, "Score: %d", score);
	Renderer::Get().Submit(
		scoreString,
		Vector2(0, Engine::Get().GetHeight() - 1)
	);
}
