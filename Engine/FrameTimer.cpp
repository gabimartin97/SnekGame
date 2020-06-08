#include "FrameTimer.h"
using namespace std::chrono;
FrameTimer::FrameTimer()
{
	zero = steady_clock::now();
	last = steady_clock::now();
}

float FrameTimer::Mark()
{
	const steady_clock::time_point old = last;
	last = steady_clock::now();
	const duration<float> deltaTime = last - old;
	return deltaTime.count();
}

float FrameTimer::Time()
{
	steady_clock::time_point now;
	now = steady_clock::now();
	const duration<float> deltaTime = now - zero;
	return deltaTime.count();

}
