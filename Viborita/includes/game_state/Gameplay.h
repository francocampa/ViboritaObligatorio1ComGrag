#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>
#include <set>
#include "IGameState.h"

class Gameplay: public IGameState {
	private:
		void handleSnakeMovement();
		void eatApple();
		void beatLevel();
		void resetLevel();
	public:
		void process();
		set<int> getThingsToDraw();
};

#endif