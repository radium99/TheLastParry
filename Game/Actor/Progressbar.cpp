#include "Progressbar.h"
#include "Render/Renderer.h"

ProgressBar::ProgressBar(int width, char fill, char empty, Color fillColor, Color emptyColor, int sortingOrder)
	: super(" ", Vector2(Engine::Get().GetWidth() / 2, Engine::Get().GetHeight() - 5)),
	//_position(pos),
	_width(width),
	_fillChar(fill),
	_emptyChar(empty),
	_fillColor(fillColor),
	_emptyColor(emptyColor),
	_currentValue(0),
	_maxValue(1),
	_sortingOrder(5)
{
}


ProgressBar::~ProgressBar()
{
}


void ProgressBar::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}
//MouseTester::MouseTester()
//	: super(" ", Vector2(Engine::Get().GetWidth() / 2, Engine::Get().GetHeight() - 1))
//{
//}
//
//void MouseTester::Tick(float deltaTime)
//{
//	super::Tick(deltaTime);
//
//	// 마우스 입력 테스트.
//	if (Input::Get().GetMouseButton(0))
//	{
//		Vector2 mousePosition = Input::Get().MousePosition();
//		char buffer[256] = {};
//		sprintf_s(
//			buffer,
//			256,
//			"cursor: (%f, %f)",
//			mousePosition.x,
//			mousePosition.y
//		);
//
//		ChangeImage(buffer);
//	}
//}

void ProgressBar::SetValue(int currentPosture, int maxPosture)
{
	_maxValue = max(1, maxPosture); // 최대값이 1이상이도록.
	_currentValue = max(0, min(currentPosture, maxPosture)); // 현재값이 최소 0이상
}

void ProgressBar::Render()
{
	// 게이지 비율 계산.
	float ratio = static_cast<float>(_currentValue) / _maxValue;
	int filledCount = static_cast<int>(_width * ratio);

	if (filledCount > 0)
	{
		std::string filledString(filledCount, _fillChar);
		Renderer::Get().Submit(filledString.c_str(), position, _fillColor, _sortingOrder);
	}

	// 빈 부분 문자열 생성 및 제출 (채워진 부분 다음 위치로)
	int emptyCount = _width - filledCount;
	if (emptyCount > 0)
	{
		std::string emptyString(emptyCount, _emptyChar);

		// 빈 부분은 filledCount만큼 떨어진 위치에 그려져야 함.
		Renderer::Get().Submit(
			emptyString.c_str(), 
			Vector2(position.x + filledCount, position.y),
			_emptyColor,
			_sortingOrder
		);
	}
}

