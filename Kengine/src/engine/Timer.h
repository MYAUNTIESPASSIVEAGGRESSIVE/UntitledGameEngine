#pragma once

class Timer
{
public:

	static void Update();
	static float GetDeltaTime() { return deltaTime; }
	static float GetElapsedTime() { return elapsedTime; }
	static float GetTimeScale() { return timeScale; }
	static void SetTimeScale(float time) { timeScale = time; };

private:

	static float deltaTime;
	static float timeScale;
	static float elapsedTime;

};

