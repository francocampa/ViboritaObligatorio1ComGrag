#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <GL/glu.h>


#include "IGameEntity.h"
#include "Block.h"
#include "Apple.h"
#include "Viborita.h"
#include "Settings.h"
#include "GameStats.h"
#include "IGameState.h"
class GameController
{
private:
	GameController();
	static GameController* instance;
	IGameState* state;
	IGameEntity* grid[8][8][8];
	Viborita* viborita;
	Settings* settings;
	GameStats* stats;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
public:
	int GRID_SIZE;
	int TILE_SIZE;
	float GRID_OFFSET;
	static GameController* getInstance();
	void processFrame(float deltaTime);
	float getGridPosition(float a);
	Viborita* getViborita();
};

