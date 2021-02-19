#include "Snake.h"
#include <assert.h>
Snake::Snake(const Location & loc_in, Board& board)
{
	segments.emplace_back(loc_in, board);
		
}

void Snake::ResetSnake(const Location & loc_in, Board& board)
{
	 selfCollided = false;
	 isCollided = false;
	 segments.clear();
	 segments.emplace_back(loc_in, board);
}

void Snake::MoveBy(const Location& delta_loc,Board& board)

{
	//Comenzamos desde el último segmento y avanzamos hacia el anterior. Todos menos la cabeza
	for (size_t i = segments.size() - 1; i > 0; i--) {
		if (i == (segments.size() - 1)) board.DespawnObject(segments[i].GetLoc()); //El último segmento limpia la casilla en la que estuvo
		segments[i].Follow(segments[i - 1]);							//Se desplaza
		board.SpawnObject(segments[i].GetLoc(), obstacleType);     //Escribe su nueva ubicación en el tablero
	}
	segments[0].MoveBy(delta_loc);  //La cabeza avanza
	board.SpawnObject(segments.front().GetLoc(), obstacleType);
}

void Snake::Grow(Board& board)
{
	Location prevSegmentLoc = segments[segments.size() -1].GetLoc();
	segments.emplace_back(prevSegmentLoc, segments.size(), board);
}

void Snake::Draw(Board& board) const
{
	for ( const auto& b : segments)
	{
		b.Draw(board);
	}
	
}

void Snake::CheckSelfCollision(const Location& next_mov)
{
	for (int i = 0; i < segments.size() - 1; i++) {
		if (segments[i].GetLoc() == next_mov) {
			selfCollided = true;
			break;
		}
	}
	
}

bool Snake::IsCollided()
{
	return (selfCollided || isCollided);
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	Location l(segments[0].GetLoc()); //Copia de la loc de la cabeza
	l.Add(delta_loc);
	return l;
}


Snake::Segment::Segment(const Location& loc_in, Board& board)
	:
	loc(loc_in),
	c(Snake::headColor)
{
	board.SpawnObject(loc, obstacleType);
}

Snake::Segment::Segment(const Location& loc_in, int createdSegments, Board& board)
	:
	loc(loc_in)
{
	board.SpawnObject(loc, obstacleType);
	if (createdSegments % 3 == 0) {
		c = bodyColor1;
	}
	else if (createdSegments % 2 == 0) {
		c = bodyColor2;
	}
	else
	{
		c = bodyColor3;
	}
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& board) const
{
	board.DrawSmallCell(loc, c);
}

const Location& Snake::Segment::GetLoc()const
{
	return loc;
}
