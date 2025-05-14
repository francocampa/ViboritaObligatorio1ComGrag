#pragma once
#include "GL/glew.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <GL/glu.h>

#include "HudController.h"
#include "GameStats.h"
#include "Settings.h"
#include "Button.h"
#include "TextField.h"
#include "Level.h"

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
	GamePlay* game;
	IGameState* state;
	Settings* settings;
	Vec2 mousePos;
	float timeCounter;
	bool showFps = false;
	int fps = 0;
	Button* fpsBtn;
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool z = false;
	bool x = false;
	bool click = false;
	bool space = false;
	bool mouseDown = false;
	bool mouseUp = false;
	bool moveCamera = true;
	std::string keyPressed = "";
public:
	int GRID_SIZE;
	int TILE_SIZE;
	float GRID_OFFSET;
	float getGridPosition(float a);
	static GameController* getInstance();
	void processFrame(float deltaTime);
	virtual std::vector<IHudElement*> getHudElements();

	void setMousePos(Vec2 mousePos);
	void setArrowUp(bool up);
	void setArrowDown(bool down);
	void setArrowLeft(bool left);
	void setArrowRight(bool right);
	void setZKey(bool z);
	void setXKey(bool x);
	void setSpaceKey(bool space);
	void setClick(bool click);
	void setMouseDown(bool click);
	void setMouseUp(bool click);
	void setShowFps(bool show);
	void setKeyPressed(std::string key);
	
	Settings* getSettings();
	void setSettings(Settings* settings);
	IGameState* getState();
	void setState(IGameState* state);
	Vec2 getMousePos();
	void setGamePlay(GamePlay* game);
	GamePlay* getGamePlay();
	bool isArrowUp();
	bool isArrowDown();
	bool isArrowLeft();
	bool isArrowRight();
	bool isZKey();
	bool isXKey();
	bool isSpaceKey();
	bool clicked();
	bool isMouseDown();
	bool isMouseUp();
	bool isShowFps();
	std::string getKeyPressed();

	void setMoveCamera(bool move);
	bool getMoveCamera();
};

