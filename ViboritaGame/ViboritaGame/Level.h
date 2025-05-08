#pragma once
#include "IGameEntity.h"
#include "Viborita.h"
#include "utils.h"
class Level
{
private:
	std::string name;
	std::string nextLevelName;
	IGameEntity* initialGrid[8][8][8];
	int maxScore;
	Viborita* initialViborita;
public:
	Level(std::string name, std::string nextLevelName, IGameEntity* initialGrid[8][8][8],int maxScore, Viborita* initialViborita);
	Level(std::string fileName, bool customLevel); //Este m[etodo deber[ia leer de un archivo y cargarlo leyendo de ah[i

	Viborita* getInitialViborita();
	IGameEntity* getInitialGridPosition(int x, int y, int z);
	int getMaxScore();
	std::string getName();
	std::string getNextLevelName();
};

