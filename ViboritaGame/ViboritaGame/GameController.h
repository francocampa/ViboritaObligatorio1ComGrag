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
#include "Cloud.h"
#include "Viborita.h"
#include "Goal.h"
#include "IGameState.h"
#include "GamePlay.h"
#include "MainMenu.h"
#include "LoadLevel.h"
#include "SettingsMenu.h"
#include "random"
#include <ctime>

class LevelCreator;
class MainMenu;
class Cloud;

class GameController
{
private:
	GameController();
	static GameController* instance;
	Settings* settings;
	
	GamePlay* game;
	MainMenu* mainMenu;
	LevelCreator* levelCreator;
	IGameState* state;

	Cloud* cloud1;
	Cloud* cloud2;
	Cloud* cloud3;
	Cloud* cloud4;

	bool paused = false;

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

	Vec3 cameraPos = { 0,0,0 };
	Vec3 cameraProps = { -M_PI / 2 , M_PI / 4 , 20 }; //theta, phi, radius
	float sensitivity = 0.5f;

	bool closeFlag = false;
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

	Vec3 getCameraProps();
	float getSensitivity();
	bool isPaused();

	void setPaused(bool paused);
	void setCameraCoordinates(float theta, float phi);
	void setCameraRadius(float radius);
	void setSensitivity(float sensitivity);

	void setCameraPos(Vec3 pos);
	Vec3 getCameraPos();

	void close();
	bool shouldClose();
};

