#include "Progressbar.h"
#include "Render/Renderer.h"
#include "Math/Color.h"		// 체력 게이지 표현
#include "Math/Vector2.h"
#include "HealthPointBar.h"

// 체력 게이지 표시에 사용할 글자 값.
// 여기에서 static은 private.
static const char* postureImages[] =
{
	" ",			// 10% 
	"  ",			// 20%
	"   ",			// 30%
	"    ",			// 40%
	"     ",		// 50%
	"      ",		// 60%
	"       ",		// 70%
	"        ",		// 80%
	"         ",	// 90%
	"          "	//100%
};

HealthPointBar::HealthPointBar(int currentValue, int maxValue, Vector2& position)
	: super("          ", position, Color::BgIntensityRed),
	_currentValue(currentValue),
	_maxValue(maxValue),
	image("          ")
{
	// 테스트: 임시 생성 위치 설정.
	//int xPosition = 5;
	//int yPosition = Engine::Get().GetHeight() - 3;
	//SetPosition(Vector2(xPosition, yPosition));
}

HealthPointBar::~HealthPointBar()
{
}


void HealthPointBar::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	// 애니메이션 재생을 위한 타이머 업데이트.
	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
	{
		return;
	}

	// 애니메이션 재생 끝났는지 확인.
	// 끝났으면 삭제.
	//if (currentSequenceIndex == effectSequenceCount - 1)
	//{
	//	Destroy();
	//	return;
	//}

	// 타이머 리셋.
	timer.Reset();

	// 이펙트 프레임 업데이트.

	// 게이지 비율 계산. (아쉬운 부분: 현재 문자를 그려놓고 이미지를 바꾸는 형식은 이 후 확장에 제한적이고 굳이 스렵다.)
	float ratio = static_cast<float>(_currentValue) / _maxValue;
	int filledIndex = static_cast<int>(round(ratio * 10.0f)) - 1; // 0~9 인덱스로 맞춤
	filledIndex = max(0, min(filledIndex, 9)); // 배열 범위 체크

	// 다음 시퀀스에서 재생할 시간으로 타이머 재설정.
	//timer.SetTargetTime(sequence[currentSequenceIndex].playTime);

	// 색상 설정.
	if (filledIndex >= 2)
	{
		color = Color::BgRed;
	}
	else if (filledIndex == 0)
	{
		color = Color::Black;
	}

	// 애니메이션 프레임에 사용할 문자열을 액터에 복사.
	ChangeImage(postureImages[filledIndex]);
}


void HealthPointBar::SetValue(int currentPosture, int maxPosture)
{
	_maxValue = max(1, maxPosture); // 최대값이 1이상이도록.
	_currentValue = max(0, min(currentPosture, maxPosture)); // 현재값이 최소 0이상
}

