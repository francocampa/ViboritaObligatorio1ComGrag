#pragma once
#include <iostream>
#include <set>
#include "Button.h"

class IGameState {
public:
	virtual void process();
	virtual void draw();
	virtual std::vector<Button*> getHudButtons();
};
