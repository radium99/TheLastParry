#include "Progressbar.h"
#include "Render/Renderer.h"

ProgressBar::ProgressBar(Vector2 pos, int width, char fill, char empty, Color fillColor, Color emptyColor, int sortingOrder)
	: _position(pos),
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
		Renderer::Get().Submit(filledString.c_str(), _position, _fillColor, _sortingOrder);
	}

	// 빈 부분 문자열 생성 및 제출 (채워진 부분 다음 위치로)
	int emptyCount = _width - filledCount;
	if (emptyCount > 0)
	{
		std::string emptyString(emptyCount, _emptyChar);

		// 빈 부분은 filledCount만큼 떨어진 위치에 그려져야 함.
		Renderer::Get().Submit(
			emptyString.c_str(), 
			Vector2(_position.x + filledCount, _position.y),
			_emptyColor,
			_sortingOrder
		);
	}
}
