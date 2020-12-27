#include "Snake.h"
#include <assert.h>
Snake::Snake(const Location & loc_in)
{
	segments[0].InitHead(loc_in);
	for (int i = 1; i <= nSegments; i++) {
		
		segments[i].InitBody(loc_in, createdSegments);
		createdSegments++;
	}
	
}

void Snake::ResetSnake(const Location & loc_in)
{
	 createdSegments = 1;
	 selfCollided = false;
	 isCollided = false;
	 nSegments = 4;

	 segments[0].InitHead(loc_in);
	 for (int i = 1; i <= nSegments; i++) {

		 segments[i].InitBody(loc_in, createdSegments);
		 createdSegments++;
	 }

}

void Snake::MoveBy(const Location & delta_loc)
{
	//Comenzamos desde el último segmento y avanzamos hacia el anterior. Todos menos la cabeza
	for (int i = nSegments - 1; i > 0; i--) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);  //La cabeza avanza
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax)
	{
		Location prevSegmentLoc = segments[nSegments - 1].GetLoc();
		segments[nSegments].InitBody(prevSegmentLoc, createdSegments);
		nSegments++;
	}
	createdSegments++;
}

void Snake::Draw(Board& board) const
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(board);
	}
	
}

void Snake::CheckSelfCollision(const Location& next_mov)
{
	for (int i = 0; i < nSegments - 1; i++) {
		if (segments[i].GetLoc() == next_mov) {
			selfCollided = true;
			break;
		}
	}
	
}

void Snake::CheckCollision(const Board& board)
{
	if (segments[0].GetLoc().x < 0 || segments[0].GetLoc().x > board.GetWidth() ||
		segments[0].GetLoc().y < 0 || segments[0].GetLoc().y > board.GetHeight())
	{
		isCollided = true;
	}

}

bool Snake::CheckFood(const Apple & apple) const
{
	if (segments[0].GetLoc().x == apple.GetLocation().x &&
		segments[0].GetLoc().y == apple.GetLocation().y)
	{
		return true;
	}else
	return false;
}

bool Snake::IsInTile(const Location & target) const
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].GetLoc() == target) //operador == sobrecargado
		{
			return true;
			break;
		}
	}
	return false;
	
	
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



void Snake::Segment::InitHead(const Location& loc_in)
{
	loc = loc_in; // El compilador asigna automáticamente cada data member
	c = Snake::headColor;
}

void Snake::Segment::InitBody(const Location& loc_in,int createdSegments)
{
	
	loc = loc_in; // El compilador asigna automáticamente cada data member
	
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
