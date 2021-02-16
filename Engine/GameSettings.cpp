#include "GameSettings.h"

GameSettings::GameSettings(std::string filename)
{
    std::ifstream settingsDocument(filename);
    std::string line;

    for (; std::getline(settingsDocument, line);)
    {
        if (line == "[Tile Size]")
        {
            settingsDocument >> tileSize;
        }
        else if (line == "[Board Size]")
        {
            settingsDocument >> boardWidth;
            settingsDocument >> boardHeight;

        }
        else if (line == "[MaxStones]")
        {
            settingsDocument >> maxStones;
        }
        else if (line == "[MaxApples]")
        {
            settingsDocument >> maxApples;
        }
        else if (line == "[MinSnekPeriod]")
        {
            settingsDocument >> minSenkPeriod;
        }
        else if (line == "[MaxPoison]")
        {
            settingsDocument >> maxPoison;
        }
        else if (line.empty())
        {
        }
        else
        {
            throw std::runtime_error("Hay boludeces en settings.txt : " + line);
        }


    }
}

int GameSettings::GetTileSize()
{
    return tileSize;
}

int GameSettings::GetBoardWidth()
{
    return boardWidth;
}

int GameSettings::GetBoardHeight()
{
    return boardHeight;
}

int GameSettings::GetMaxStones()
{
    return maxStones;
}

int GameSettings::GetMaxApples()
{
    return maxApples;
}
int GameSettings::GetMaxPosion()
{
    return maxPoison;
}

float GameSettings::GetMinSnekPeriod()
{
    return minSenkPeriod;
}
