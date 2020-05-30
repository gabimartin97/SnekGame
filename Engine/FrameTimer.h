#pragma once

#include <chrono>

class FrameTimer {
public:
	FrameTimer();
	float Mark(); //Retorna el tiempo que pas� desde su �ltima llamada

private:
	std::chrono::steady_clock::time_point last;
};