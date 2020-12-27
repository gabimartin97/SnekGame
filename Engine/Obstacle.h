#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Board.h"
class Obstacle {

public:
	
	void Draw(Board& board) const;
	void Spawn(int x_in, int y_in, Board& board);
	void Spawn(const Location& loc_in, Board& board);
	Location GetLocation() const;

private:
	Location loc;
	const Color c = Colors::Gray;

};