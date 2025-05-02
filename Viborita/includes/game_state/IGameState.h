#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <iostream>
#include <set>

class IGameState {
	public:
		virtual void process();
		virtual set<int> getThingsToDraw();
};

#endif