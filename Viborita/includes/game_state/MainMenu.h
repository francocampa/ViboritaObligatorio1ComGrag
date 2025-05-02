#ifndef MAINMENU_H
#define MAINMENU_H

#include <iostream>
#include <set>
#include "IGameState.h"

class MainMenu : public IGameState {
	private:
		void startLevel();
		set<int> getLevelsList();
	public:
		void process();
		set<int> getThingsToDraw();
};

#endif