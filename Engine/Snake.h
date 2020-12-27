#pragma once
#include "Board.h"
#include "Apple.h"
class Snake {
private:
		class Segment {
		public:
			void InitHead(const Location& loc_in); //Toma como parámetro la posición de la cabeza
			void InitBody(const Location& loc_in, int createdSegments);			//Inicializar segmentos cuando la snake crece. No toma parámetros porque sigue al segm. anterior.
			void Follow(const Segment& next);
			void MoveBy(const Location& delta_loc);
			void Draw(Board& board) const;
			const Location& GetLoc() const; //Función que retorna la REFERENCIA a loc del segmento, Para no hacer copia

		private:
			Location loc;
			Color c;
			
		};

public:
	Snake(const Location& loc_in);
	void ResetSnake(const Location& loc_in);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw(Board& board) const; //Porque no puedo coner const aca?
	void CheckSelfCollision(const Location& next_mov) ;
	void CheckCollision(const Board& board);
	bool CheckFood(const Apple& apple) const;
	bool IsInTile(const Location& target) const;
	bool IsCollided();
	Location GetNextHeadLocation(const Location& delta_loc) const;

private: //Este otro private simplemente es visual, como par separar cosas
	static constexpr Color headColor = Colors::MakeRGB(204,204,0);
	static constexpr Color bodyColor1 = Colors::MakeRGB(0,102,51);
	static constexpr Color bodyColor2 = Colors::MakeRGB(0, 102, 0);
	static constexpr Color bodyColor3 = Colors::MakeRGB(0, 80, 21);
	static constexpr int nSegmentsMax = 100;

	int nSegments = 4; //points to the next unused member of the segment array
	int createdSegments = 1;
	bool selfCollided = false;
	bool isCollided = false;
	Segment segments[nSegmentsMax];
	Location loc;
};