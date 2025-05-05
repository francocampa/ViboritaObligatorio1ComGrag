#pragma once
#include "IGameState.h"
#include <set>

class MainMenu :
    public IGameState
{
private:
	void startLevel();
	std::set<int> getLevelsList();
public:
	void process();
	void draw();
};

