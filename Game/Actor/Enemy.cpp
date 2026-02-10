#include "Enemy.h"
#include "Util/Util.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Actor/EnemyDestroyEffect.h"
#include "Core/Input.h"

Enemy::Enemy(const char* image)
	: super(image, Vector2::Zero, Color::Red, 0, 100, 1, 1) // 초기화
	
{
	//// 테스트: 임의로 플레이어 위치를 하드코딩으로 맞춤.
	//playerTargetPosition = Vector2(Engine::Get().GetWidth() / 2.0f + 1, Engine::Get().GetHeight() - 5.0f);

	// 랜덤 생성. 0: 오른쪽, 1: 왼쪽, 2: 위쪽
	int randomDir = Util::Random(0, 2);

	// 테스트: 플레이어 위치와 임의로 맞춤.
	float xVec = Engine::Get().GetWidth() / 2.0f + 1;
	float yVec = Engine::Get().GetHeight() - 5.0f;

	if (randomDir == 0)
	{
		// 화면 오른쪽에서 생성. "(oOo)"
		direction = MoveDirection::Left;
		xPosition = static_cast<float>(
			Engine::Get().GetWidth() - width - 1
			);
		yPosition = yVec;
	}
	else if(randomDir == 1)
	{
		// 화면 왼쪽에서 생성.
		direction = MoveDirection::Right;
		xPosition = 0.0f;
		yPosition = yVec;

	}
	else // random == 2
	{
		// 화면 위쪽에서 생성.
		direction = MoveDirection::Down;
		//xPosition = 0.0f;
		xPosition = xVec - width - 1;
	}

	// 이동 방향에 따른 적 위치 설정.
	SetPosition(
		Vector2(static_cast<int>(xPosition), static_cast<int>(yPosition))
	);

	// 발사 타이머 목표 시간 설정.
	timer.SetTargetTime(Util::RandomRange(1.0f, 3.0f));
}

Enemy::~Enemy()
{
}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);


	/*position.x += 20.0f * deltaTime;*/

	/*Vector2 UnitVector = directionVector.ChangeToUnitVector();*/
	//position = position + UnitVector * moveSpeed * deltaTime;


	// 이동 처리.
	if (direction == MoveDirection::Left)
	{
		float dir = -1.0f;
		xPosition = xPosition + moveSpeed * dir * deltaTime;
	}
	else if (direction == MoveDirection::Right)
	{
		float dir = 1.0f;
		xPosition = xPosition + moveSpeed * dir * deltaTime;
	}
	else if (direction == MoveDirection::Down)
	{
		float dir = 1.0f;
		yPosition = yPosition + moveSpeed * dir * deltaTime;
	}


	if (Input::Get().GetKeyDown(VK_SPACE)) // 테스트: ProgressBar와 연결 확인.
	{
		TakePostureDamage(10);
		if (progressBar)
		{
			progressBar->SetValue(currentPosture, maxPosture);
		}
	}



	// 좌표 검사.
	// 화면 왼쪽을 완전히 벗어났으면.
	if (xPosition + width < 0)
	{
		Destroy();
		return;
	}

	// 화면 오른쪽을 완전히 벗어났으면.
	if (xPosition > Engine::Get().GetWidth() - 1)
	{
		Destroy();
		return;
	}

	// 화면 아래쪽을 완전히 벗어났으면.
	if (yPosition >= Engine::Get().GetHeight())
	{
		Destroy();
		return;
	}

	// 위치 설정.
	SetPosition(Vector2(
		static_cast<int>(xPosition),
		static_cast<int>(yPosition)
	));



	// 테스트: 플레이어 체간 데미지 입력 처리.
	if (Input::Get().GetKeyDown(VK_DELETE))
	{
		OnDamaged(120, 100);
	}

	// 발사 타이머 업데이트.
	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
	{
		return;
	}

	// 타이머 리셋.
	timer.Reset();

	//// 탄약 발사.
	//GetOwner()->AddNewActor(new EnemyBullet(
	//	Vector2(position.x + width / 2, position.y),
	//	Util::RandomRange(10.0f, 20.0f)
	//));

}

void Enemy::OnDamaged(int postureDmg, int hpDmg)
{
	TakePostureDamage(postureDmg);

	// ==인 이유는 TakePostureDamage()에서 maxPosture를 초과하는 dmg를 받았을 때, maxPosture와 수치를 같게 만들어줌.
	if (currentPosture == maxPosture || TakeHealthPointDamage(hpDmg) == 0)
	{
		// 액터 제거.
		Destroy();
		// 이펙트 생성 (재생을 위해).
		GetOwner()->AddNewActor(new EnemyDestroyEffect(position));
	}

}


Vector2 Enemy::GetProgressBarPosition() const
{
	//int xPosition = position.x;
	//int yPosition = position.y-1;
	return Vector2(position.x, position.y - 1);

}