#include "Time.h"

INT64 Time::frequency = 0;
float Time::ticksPerMs = 0;
INT64 Time::startTime = 0;
float Time::deltaTime = 0;

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
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);
	timeDifference = (float)(currentTime - startTime);

	deltaTime = timeDifference / ticksPerMs;
	deltaTime /= 1000;
	return;
}