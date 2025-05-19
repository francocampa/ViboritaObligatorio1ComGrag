#pragma once
#include "IGameState.h"
#include "Button.h"
#include "Level.h"
#include "GameStats.h"
#include "GameController.h"

class GamePlay :
    public IGameState
{
private:
	Button* settings;
	Button* reset;
	Button* scoreText;
	Button* timerText;
	Level* level;
	IGameEntity* grid[8][8][8];
	Viborita* viborita;
	GameStats* stats;

public:
	GamePlay(Level* level);
	void process(float deltaTime);
	void changeTimer(int time);
	void beatLevel();
	void startLevel();
	void resetLevel();
	void addSecond();
	void draw();
	std::vector<IHudElement*> getHudElements();

	Viborita* getViborita();
	bool tileHasApple(Vec3 indices);
	void clearTile(Vec3 indices);
	bool validTile(Vec3 indices);
	bool hasSolidBlock(Vec3 indices);
	bool hasViborita(Vec3 indices);
	bool hasGoal(Vec3 indices);
	void addViborita(Vec3 indices);
	void eatAppleAt(Vec3 indices);
	void ateApple();

	~GamePlay();
};

