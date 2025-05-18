#pragma once
#include "GameController.h"
#include "IGameEntity.h"
#include "utils.h"

class Cloud
{
private:
	int type;
	Vec3 position;
	float angle;
	float angleSpeed;
	float radio;
public:
	Cloud(int type, float radio, float angle);
	GAME_ENTITY_TYPE getType();
	void draw(float deltaTime);
	void setCloudAngle(float angle);
};

