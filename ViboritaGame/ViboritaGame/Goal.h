#pragma once
#include "IGameEntity.h"
#include "utils.h"
class Goal :
    public IGameEntity
{
private:
	Vec3 position;
	Vec3 gridIndex;
	float angle;
	GLfloat goal[12];
public:
	Goal(Vec3 gridIndexes, Vec3 position);
	void process(float deltaTime);
	void draw();
	GAME_ENTITY_TYPE getType();
	Vec3 getPosition() { return this->position; }
	Vec3 getGridIndexes() { return this->gridIndexes; }
};

