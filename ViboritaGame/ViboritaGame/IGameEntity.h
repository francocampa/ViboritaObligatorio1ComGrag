#pragma once
#include <set>

class IGameEntity
{
public:
	virtual void process(float deltaTime);
	virtual void draw();
};

