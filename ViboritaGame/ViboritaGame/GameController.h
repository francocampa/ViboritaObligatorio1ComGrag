#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <GL/glu.h>


#include "IGameEntity.h"
#include "Block.h"

class GameController
{
private:
	GameController();
	static GameController* instance;
	IGameEntity* grid[8][8][8];
public:
	int GRID_SIZE;
	int TILE_SIZE;
	float GRID_OFFSET;
	static GameController* getInstance();
	void processFrame(float deltaTime);
	float getGridPosition(float a);
};

