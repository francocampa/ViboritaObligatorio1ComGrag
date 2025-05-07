#pragma once
#include "IGameState.h"
#include <set>
#include "Button.h"

class MainMenu :
    public IGameState
{
private:
	void startLevel();
	std::set<int> getLevelsList();
public:
	void process();
	void draw();
	virtual std::vector<Button*> getHudButtons();
};

