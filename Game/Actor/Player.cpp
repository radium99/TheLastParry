#include "Player.h"
#include "Actor/PlayerBullet.h"
#include "Core/Input.h"
#include "Engine/Engine.h"
#include "Level/Level.h"
#include "Render/Renderer.h"
#include "Util/Timer.h"
#include <iostream>


Player::Player()
	: super("*(o.o)/", Vector2::Zero, Color::Green, 0, 100),
	fireMode(FireMode::OneShot)
{
	// 생성 위치 설정.
	float xPosition = (Engine::Get().GetWidth() / 2) - width;
	float yPosition = Engine::Get().GetHeight() - 5;
	SetPosition(Vector2(xPosition, yPosition));

	// 타이머 목표 시간 설정.
	//timer.SetTargetTime(fireInterval);
	timer.SetTargetTime(0.0165f);

	// 테스트용:플레이어 체간 시각화.
	ShowPosture();

}

Player::~Player()
{
}

void Player::BeginPlay()
{
	super::BeginPlay();

	// ProgressBar 생성 및 연결(값 전달).
	playerProgressBar = new ProgressBar(currentPosture, maxPosture);
	GetOwner()->AddNewActor(playerProgressBar);
}

void Player::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 종료 처리.
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		// 게임 종료.
		QuitGame();
	}

	if (Input::Get().GetKeyDown(VK_DOWN)) // 테스트: ProgressBar와 연결 확인.
	{
		TakePostureDamage(10);
		if (playerProgressBar)
		{
			playerProgressBar->SetValue(currentPosture, maxPosture);
		}
	}

	// 테스트용: 플레이어 체간 시각화.
	ShowPosture();


	// 경과 시간 업데이트.
	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
	{
		return;
	}
	timer.Reset();

	//Move();
	//이동 처리. 임경우
	//Move(deltaTime);
	//Vector2 mousePos = Input::Get().MousePosition(); // 마우스 위치 가져오기.
	//Vector2 UnitVector = mousePos - position; // 방향벡터.

	//UnitVector.ChangeToUnitVector(); // 정수 받아 유클리드 거리 공식으로  단위 벡터 만들기.


	//position = position + UnitVector* speed * deltaTime; // 실질적 위치 이동 코드.
	//position = position + UnitVector; // 실질적 위치 이동 코드.
	// 위치 이동 코드. (계단현상: 스캔라인 형태)
	
	/*position.x = position.x + UnitVector.x;
	position.y = position.y + UnitVector.y;*/
	// 
	// 좌표 검사.
	if (position.x + width + 5 > Engine::Get().GetWidth())
	{
		position.x -= 1; //Engine::Get().GetWidth() - width;
	}
	if (position.y > Engine::Get().GetHeight())
	{
		position.y -= 1; ///Engine::Get().GetWidth();
	}


	// 플레이어 체간 데미지 입력 처리.
	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		TakePostureDamage(10);
		playerProgressBar->SetValue(currentPosture, maxPosture);
	}

	//플레이어 위치 출력
	//ShowPos(position);

    // Pseudocode:
    // 1. 버퍼를 준비한다.
    // 2. position.x 값만 소수점 둘째자리까지 포맷하여 문자열로 만든다.
    // 3. Renderer에 문자열을 제출하여 화면에 표시한다.


	// 좌우 방향키 입력처리.
	//if (Input::Get().GetKey(VK_LEFT))
	//{
	//	MoveLeft();
	//}
	//if (Input::Get().GetKey(VK_RIGHT))
	//{
	//	MoveRight();
	//}

	//// 스페이스 키를 활용해 탄약 발사.
	if (fireMode == FireMode::OneShot)
	{
		if (Input::Get().GetKeyDown(VK_LEFT))
		{
			Fire(0);
		}
		if (Input::Get().GetKeyDown(VK_UP))
		{
			Fire(1);
		}
		if (Input::Get().GetKeyDown(VK_RIGHT))
		{
			Fire(2);
		}
		if (Input::Get().GetKeyDown(VK_DOWN))
		{
			Fire(3);
		}

	}
	//else if (fireMode == FireMode::Repeat)
	//{
	//	if (Input::Get().GetKey(VK_SPACE))
	//	{
	//		FireInterval();
	//	}
	//}

	//// 발사 모드 전환.
	//if (Input::Get().GetKeyDown('R'))
	//{
	//	int mode = static_cast<int>(fireMode);
	//	mode = 1 - mode;
	//	fireMode = static_cast<FireMode>(mode);
	//}

}
void Player::ShowPosture()
{
	static char xPosString[128] = { 0 };
	std::snprintf(xPosString, sizeof(xPosString), "Player Pousture: %d / %d", currentPosture, maxPosture);
	Renderer::Get().Submit(xPosString, Vector2(8, 19));
}
void Player::ParryingTime()
{
}
//void Player::AddPlayerProgressBar()
//{
//    // ProgressBar는 타입 이름이므로, 인스턴스를 생성해야 합니다.
//    // 예시: ProgressBar* progressBar = new ProgressBar();
//    // 그리고 AddNewActor에 progressBar를 전달해야 합니다.
//    // ProgressBar 클래스가 생성자 인자를 필요로 한다면 적절히 전달해야 합니다.
//
//    playerProgressBar = new ProgressBar(currentPosture, maxPosture); // 필요시 생성자 인자 추가
//    GetOwner()->AddNewActor(playerProgressBar);
//    // 반환값이 ProgressBar 인스턴스라면 아래처럼 반환
//    // return progressBar;
//}


void Player::Move() // 임경우.
{
	Vector2 mousePos = Input::Get().MousePosition(); // 마우스 위치 가져오기.
	//Vector2 UnitVector= mousePos - position; // 방향벡터.
	Vector2 UnitVector;
	UnitVector.x = mousePos.x - position.x;
	UnitVector.y = mousePos.y - position.y;

	float len = sqrtf(((mousePos.x - position.x) * (mousePos.x - position.x)) + ((mousePos.y - position.y) * (mousePos.y - position.y)));
	if (len)
	{
		UnitVector.x /= len;
		UnitVector.y /= len;
	}

	float deltaX = position.x - mousePos.x;
	float deltaY = position.y - mousePos.y;
	
	//UnitVector.ChangeToUnitVector(); // 정수 받아 유클리드 거리 공식으로  단위 벡터 만들기.
	
	// 위치 이동 코드.
	//position.x = position.x + UnitVector.x ; // * 실수형 deltaTime 빠짐.
	//position.y = position.y + UnitVector.y;

		
	// 이동 예시 코드:
	//position.x = mousePos.x;
	//position.y = mousePos.y;
}

void Player::MoveRight()
{
	// 오른쪽 이동 처리.
	position.x += 1;

	// 좌표 검사.
	// "<-=A=->"
	if (position.x + width > Engine::Get().GetWidth())
	{
		position.x -= 1;
	}
}

void Player::MoveLeft()
{
	// 왼쪽 이동 처리.
	position.x -= 1;

	// 좌표 검사.
	if (position.x < 0)
	{
		position.x = 0;
	}
}

void Player::Fire(int dir) // dir 0: left, 1: up, 2: right, 3: down(down은 확장 가능성)
{
	// 경과 시간 초기화.
	//elapsedTime = 0.0f;
	timer.Reset();

	int xVec = position.x;
	int yVec = position.y;

	// 방향 위치 설정.
	switch (dir)
	{
	case 0:
		// 왼쪽이면 position.x = position.x - 1;
		xVec = position.x - 1;
		break;
	case 1:
		// 업이면 position.x = positon.x - 1;
		xVec = position.x + (width / 2);
		yVec = position.y - 1;
		break;
	case 2:
		// 오른쪽이면 position.x = position.x - 1;
		xVec = position.x + width + 1;
		break;
	default:
		xVec = position.x + (width / 2);
		yVec = position.y + 1;
		break;
	}
	Vector2 bulletPosition(xVec, yVec);

	// 액터 생성.
	GetOwner()->AddNewActor(new PlayerBullet(bulletPosition));
}

//void Player::FireInterval()
//{
//	// 발사 가능 여부 확인.
//	if (!CanShoot())
//	{
//		return;
//	}
//
//	// 발사.
//	Fire();
//}

bool Player::CanShoot() const
{
	// 경과 시간 확인.
	// 발사 간격보다 더 많이 흘렀는지.
	return timer.IsTimeOut();
}

