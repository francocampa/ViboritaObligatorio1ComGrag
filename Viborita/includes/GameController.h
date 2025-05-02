#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include <set>
#include "./game_state/IGameState.h"
#include "./game_entities/IGameEntity.h"

class GameController : public IGameState {
private:
	static GameController* instance;
	GameController();
	IGameState* gameState;
	IGameEntity grid[8][8][8];
public:
	void handleFrame();
};

#endif