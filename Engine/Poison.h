#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Board.h"
class Poison {

public:

	void Draw(Board& board) const;
	void Spawn(int x_in, int y_in, Board& board, const unsigned index);
	void Spawn(const Location& loc_in, Board& board, const unsigned index);
	void Despawn(Board& board);
	bool IsEaten()const;
	Location GetLocation() const;

private:
	Location loc;
	const Color c = Colors::MakeRGB(158,128,192);
	static constexpr int obstacleType = 2;
	bool isEaten = false;
};