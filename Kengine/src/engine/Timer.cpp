#include "Timer.h"
#include <chrono>

float Timer::deltaTime = 0;
float Timer::elapsedTime = 0;

void Timer::Update()
{
	using namespace std::chrono;
	static steady_clock::time_point last = steady_clock::now();

	steady_clock::time_point now = steady_clock::now();
	deltaTime = duration_cast<microseconds>(now - last).count() / 1000000.0f;
	last = now;

	elapsedTime += deltaTime;
}
