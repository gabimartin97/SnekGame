#pragma once
//#include "Location.h" Ya están en Board.h
//#include "Graphics.h"
#include "Board.h"




class Apple {
	
public:
	Apple(const Location& loc_in);
	void Draw(Board& board) const;
	void Respawn(int x, int y);
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

};