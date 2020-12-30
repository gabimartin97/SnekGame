#pragma once
#include "Board.h"
//#include "Apple.h"
class Snake {
private:
	class Segment {
	public:
		void InitHead(const Location& loc_in,  Board& board); //Toma como parámetro la posición de la cabeza
		void InitBody(const Location& loc_in, int createdSegments,  Board& board);			//Inicializar segmentos cuando la snake crece. No toma parámetros porque sigue al segm. anterior.
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& board) const;
		const Location& GetLoc() const; //Función que retorna la REFERENCIA a loc del segmento, Para no hacer copia

	private:
		Location loc;
		Color c;
		Board::CellObjects obstacleType = Board::CellObjects::Snek;

	};

public:
	Snake(const Location& loc_in, Board& board);
	void ResetSnake(const Location& loc_in, Board& board);
	void MoveBy(const Location& delta_loc, Board& board);
	void Grow(Board& board);
	void Draw(Board& board) const; 
	void CheckSelfCollision(const Location& next_mov);
	bool IsCollided();
	Location GetNextHeadLocation(const Location& delta_loc) const;

private: //Este otro private simplemente es visual, como par separar cosas
	static constexpr Color headColor = Colors::MakeRGB(204, 204, 0);
	static constexpr Color bodyColor1 = Colors::MakeRGB(0, 102, 51);
	static constexpr Color bodyColor2 = Colors::MakeRGB(0, 102, 0);
	static constexpr Color bodyColor3 = Colors::MakeRGB(0, 80, 21);
	static constexpr int nSegmentsMax = 100;
	Board::CellObjects obstacleType = Board::CellObjects::Snek;
	int nSegments = 2; //points to the next unused member of the segment array
	int createdSegments = 1;
	bool selfCollided = false;
	bool isCollided = false;
	Segment segments[nSegmentsMax];
	Location loc;
};