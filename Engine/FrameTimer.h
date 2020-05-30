#pragma once

#include <chrono>

class FrameTimer {
public:
	FrameTimer();
	float Mark(); //Retorna el tiempo que pasó desde su última llamada

private:
	std::chrono::steady_clock::time_point last;
};