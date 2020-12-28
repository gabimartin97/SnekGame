#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Board.h"
class Obstacle {

public:
	
	void Draw(Board& board) const;
	void Spawn(int x_in, int y_in, Board& board, const unsigned int index);
	void Spawn(const Location& loc_in, Board& board, const unsigned int index);
	Location GetLocation() const;

private:
	Location loc;
	const Color c = Colors::Gray;
	static constexpr int obstacleType = 1;
};