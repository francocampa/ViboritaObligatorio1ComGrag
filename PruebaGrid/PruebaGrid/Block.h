#pragma once
#include "IGameEntity.h"
#include "utils.h"

class Block :
    public IGameEntity
{
private:
	Vec3 position;
	GLfloat cube[24];
public:
	Block(Vec3 position);
	void process(float deltaTime);
	void draw();
};

