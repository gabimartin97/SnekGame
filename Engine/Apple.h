#pragma once
//#include "Location.h" Ya est�n en Board.h
//#include "Graphics.h"
#include "Board.h"




class Apple {
	
public:
	Apple(const Location& loc_in, Board& board);
	void Draw(Board& board) const;
	void Respawn(int x, int y, Board& board);
	void Respawn(Location& loc_in, Board& board);
	void Update();
	Location GetLocation() const;
	
	//void CheckCollision(const Location& snake_loc);

private:
	Location loc;
	Color c = Colors::Red;
	bool isEaten = false;
	bool isCollided = false;
	bool colorIncrement = true;
	int r = 200;
	int g = 0;
	int b = 0;
	static constexpr int obstacleType = 3;

};