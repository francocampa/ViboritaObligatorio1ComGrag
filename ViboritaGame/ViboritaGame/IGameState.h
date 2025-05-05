#pragma once
#include <iostream>
#include <set>

class IGameState {
public:
	virtual void process();
	virtual void draw();
};
