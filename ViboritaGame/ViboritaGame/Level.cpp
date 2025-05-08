#include "Level.h"

Level::Level(std::string name, IGameEntity* initialGrid[8][8][8], int maxScore, Viborita* initialViborita)
{
	this->name = name;
	this->initialViborita = initialViborita;
	this->maxScore = maxScore;
	for (int x = 0; x < 8;x++) {
		for (int y = 0; y < 8;y++) {
			for (int z = 0; z < 8;z++) {
				this->initialGrid[x][y][z] = initialGrid[x][y][z];
			}
		}
	}
}

Level::Level(std::string fileName, bool customLevel)
{
	//TODO: definir qu[e tipo de archivo y el formato
	//Pa mi un .txt pelado con un formato nuestro ser[ia lo m[as f[acil de hacer a mano
	//Si no investigar una librer[ia de json/xml y ver si lo podemos armar para que al cargarlo cree
	//un objeto Level
}

IGameEntity* Level::getInitialGridPosition(int x, int y, int z)
{
	return initialGrid[x][y][z];
}

Viborita* Level::getInitialViborita()
{
	return initialViborita->deepCopy();
}

int Level::getMaxScore()
{
	return maxScore;
}

