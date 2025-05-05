#pragma once
#include "IGameState.h"
class LoadLevel :
    public IGameState
{
private:
	bool loading;
	void readLevelFile();
	void processLevel();
	void startGameplay();
public:
	void process();
	void draw();
};

