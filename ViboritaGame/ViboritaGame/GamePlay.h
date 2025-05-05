#pragma once
#include "IGameState.h"
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
};

