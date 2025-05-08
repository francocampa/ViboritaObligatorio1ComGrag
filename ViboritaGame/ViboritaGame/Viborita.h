#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <GL/glu.h>
#include "utils.h"
#include <vector>
#include "IGameEntity.h"
//#include "GamePlay.h"

class GamePlay;

class Viborita :
	public IGameEntity
{
private:
	GamePlay* gameContext;
	GLfloat viboritaColors[24];
	ViboritaBody body;
	Vec3 headDirection;
	Vec3 prevMovement;
public:
	Viborita(Vec3 gridPosition,Vec3 position, GLfloat colors[24]);
	void setGameContext(GamePlay* context);
	void process(float deltaTime);
	void draw();
	ViboritaPart* getHead();
	void setHead();
	void addTail(Vec3 gridPosition);
	Vec3* getMovementDirection();
	void handleMovement(Vec3* movementDir);
	void handleEatApple(Vec3* lastTailPos,Vec3* lastTailGrid);
	bool hasFloor();
	void handleFall();
	void handleDeath();
	GAME_ENTITY_TYPE getType();
};

