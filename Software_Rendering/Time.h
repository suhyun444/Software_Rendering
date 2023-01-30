#pragma once
#include <Windows.h>

class Time
{
private:
	static INT64 frequency;
	static float ticksPerMs;
	static INT64 startTime;
	static float deltaTime;
public:

	static bool Initialize();
	static void Frame();
	static float GetDeltaTime() {return deltaTime;}
};
