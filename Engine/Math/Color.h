#pragma once

#include "Common/Common.h"
#include <Windows.h>

namespace Wanted
{
	// 콘솔에 텍스트 색상 등을 지정할 때 사용할
	// 색상 열거형.
	enum class WANTED_API Color : unsigned short
	{
		Black = 0,
		Blue = FOREGROUND_BLUE,// 전경
		Green = FOREGROUND_GREEN,
		Red = FOREGROUND_RED,
		Yellow = FOREGROUND_RED | FOREGROUND_GREEN,
		White = Blue | Green | Red,
		BgBlue = BACKGROUND_BLUE,// 배경
		BgGreen = BACKGROUND_GREEN,
		BgRed = BACKGROUND_RED,
		BgIntensity = BACKGROUND_INTENSITY,
		BgYellow = BACKGROUND_RED | BACKGROUND_GREEN,
		BgIntensityYellow = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
		BgIntensityRed = BACKGROUND_RED | BACKGROUND_INTENSITY
	};
}