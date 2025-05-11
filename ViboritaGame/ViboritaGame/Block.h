#pragma once
#include "utils.h"
#include "IGameEntity.h"

class Block :
	public IGameEntity
{
private:
	GLfloat cube[24];
public:
	Block(Vec3 gridIndexes, Vec3 position);
	void process(float deltaTime);
	void draw();
	GAME_ENTITY_TYPE getType();
};

