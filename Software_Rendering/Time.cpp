#include "Time.h"

bool Time::Initialize()
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);
	if (frequency == 0)
	{
		return false;
	}

	ticksPerMs = (float)(frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER *)&startTime);

	return true;
}

void Time::Frame()
{
	INT64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	startTime = currentTime;

	return;
}

float Time::GetDeltaTime()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	timeDifference = (float)(currentTime - startTime);

	frameTime = timeDifference / ticksPerMs;
	return frameTime / 1000;
}