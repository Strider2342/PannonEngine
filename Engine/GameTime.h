#pragma once
#include <iostream>
#include <chrono>

using namespace std::chrono;

class GameTime
{
	time_point<system_clock> startTime;
	time_point<system_clock> prevTime;

public:
	GameTime();

	float GetElapsedTime();
	float GetDeltaTime();

	void SetPrevTime();
};