#pragma once
#include<fstream>
#include<string>

class GameSettings
{
	
public:
	GameSettings(std::string filename);
	int GetTileSize();
	int GetBoardWidth();
	int GetBoardHeight();
	int GetMaxStones();
	int GetMaxApples();
	int GetMaxPosion();
	float GetMinSnekPeriod();


private:
	int tileSize;
	int boardWidth;
	int boardHeight;
	int maxStones;
	int maxApples;
	int maxPoison;
	float minSenkPeriod;


};