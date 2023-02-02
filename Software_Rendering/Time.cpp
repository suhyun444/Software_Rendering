#include "Time.h"

INT64 Time::frequency = 0;
float Time::ticksPerMs = 0;
INT64 Time::startTime = 0;
float Time::deltaTime = 0;
int Time::frameCount = 0;
int Time::curFrameCount = 0;
float Time::frameTime = 0;

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
	CountFrame();
	return;
}
void Time::CountFrame()
{
	frameTime += deltaTime;
	curFrameCount++;
	if (frameTime >= 1.0f)
	{
		frameTime = 0.0f;
		frameCount = curFrameCount;
		curFrameCount = 0;
	}
}
void Time::Update()
{
	INT64 currentTime;
	QueryPerformanceCounter((LARGE_INTEGER *)&currentTime);

	float timeDifference;
	timeDifference = (float)(currentTime - startTime);

	deltaTime = timeDifference / ticksPerMs;
	deltaTime /= 1000.0f;
}