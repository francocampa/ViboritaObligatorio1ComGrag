#pragma once
#include "IGameState.h"
#include "Button.h"

class GamePlay :
    public IGameState
{
private:
	void handleSnakeMovement();
	void eatApple();
	void beatLevel();
	void resetLevel();
public:
	void process();
	void draw();
	std::vector<Button*> getHudButtons();
};

