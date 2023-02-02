#pragma once
#include <Windows.h>
#include <iostream>

class Time
{
private:
	static INT64 frequency;
	static float ticksPerMs;
	static INT64 startTime;
	static float deltaTime;
	static int frameCount;
	static int curFrameCount;
	static float frameTime;
public:

	static bool Initialize();
	static void Frame();
	static void CountFrame();
	static void Update();
	static float GetDeltaTime() {return deltaTime;}
	static LPCTSTR GetFrameCount(char* buffer)
	{
		_itoa(frameCount, buffer, 10);
		return (LPCTSTR)buffer;
	}
};
