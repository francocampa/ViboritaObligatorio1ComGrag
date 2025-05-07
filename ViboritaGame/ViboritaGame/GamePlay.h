#pragma once
#include "IGameState.h"
#include "Button.h"
#include "GameStats.h"
#include "GameController.h"

class GamePlay :
    public IGameState
{
private:
	Button* settings;
	Button* scoreText;
	Button* timerText;
public:
	GamePlay();
	void process();
	void eatApple();
	void changeTimer(const char* time);
	void beatLevel();
	void resetLevel();
	void draw();
	std::vector<Button*> getHudButtons();
};

