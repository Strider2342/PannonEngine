#include "GameTime.h"

GameTime::GameTime()
{ 
	startTime = system_clock::now();
}

float GameTime::GetElapsedTime()
{
	time_point<system_clock> currentTime = system_clock::now();
	duration<float> elapsedSec = currentTime - startTime;
	
	return elapsedSec.count();
}

float GameTime::GetDeltaTime()
{
	time_point<system_clock> currentTime = system_clock::now();
	duration<float> elapsedSec = currentTime - prevTime;

	float elapsed = floorf(elapsedSec.count() * 10000.0f);

	return elapsed / 10000.0f;
}

void GameTime::SetPrevTime()
{
	prevTime = system_clock::now();
}
