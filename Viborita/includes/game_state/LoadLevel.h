#ifndef LOADLEVEL_H
#define LOADLEVEL_H

#include <iostream>
#include <set>
#include "IGameState.h"

class LoadLevel : public IGameState {
private:
	void readLevelFile();
	void processLevel();
	void startGameplay();
public:
	void process();
	set<int> getThingsToDraw();
};

#endif