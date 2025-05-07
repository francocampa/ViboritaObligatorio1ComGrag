#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <GL/glu.h>

#include "HudController.h"
#include "GameStats.h"
#include "Settings.h"
#include "Button.h"

#include "IGameEntity.h"
#include "Block.h"
#include "Apple.h"
#include "Viborita.h"
#include "Goal.h"
#include "IGameState.h"
#include "GamePlay.h"
#include "MainMenu.h"
#include "LoadLevel.h"
#include "MainMenu.h"
#include "SettingsMenu.h"

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
	Vec2 mousePos;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool z = false;
	bool x = false;
	bool click = false;
public:
	int GRID_SIZE;
	int TILE_SIZE;
	float GRID_OFFSET;
	static GameController* getInstance();
	void processFrame(float deltaTime);
	float getGridPosition(float a);
	virtual std::vector<Button*> getHudButtons();
	Viborita* getViborita();
	bool tileHasApple(Vec3 indices);
	void clearTile(Vec3 indices);
	bool validTile(Vec3 indices);
	bool hasSolidBlock(Vec3 indices);
	bool hasViborita(Vec3 indices);
	void addViborita(Vec3 indices);
	void ateApple();

	void setMousePos(Vec2 mousePos);
	void setArrowUp(bool up);
	void setArrowDown(bool down);
	void setArrowLeft(bool left);
	void setArrowRight(bool right);
	void setZKey(bool z);
	void setXKey(bool x);
	void setClick(bool click);
	
	IGameState* getState();
	GameStats* getStats();
	Vec2 getMousePos();
	bool isArrowUp();
	bool isArrowDown();
	bool isArrowLeft();
	bool isArrowRight();
	bool isZKey();
	bool isXKey();
	bool clicked();
};

