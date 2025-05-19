#pragma once
#include "IGameEntity.h"
#include "GameController.h"
#include "utils.h"

class PeaksApple :
    public IGameEntity
{
private:
	Vec3 position;
	Vec3 gridIndex;
public:
	PeaksApple(Vec3 girdIndex, Vec3 position);
	GAME_ENTITY_TYPE getType();
	void process(float deltaTime);
	void draw();
};

