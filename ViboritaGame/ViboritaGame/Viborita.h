#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <GL/glu.h>
#include <iostream>
#include "utils.h"
#include <vector>
#include "IGameEntity.h"

class Viborita :
	public IGameEntity
{
private:
	GLfloat viboritaColors[24];
	ViboritaBody body;
	Vec3 headDirection;
public:
	Viborita(Vec3 gridPosition,Vec3 position, GLfloat colors[24] );
	void process(float deltaTime);
	void draw();
	Vec3* getMovementDirection();
	void handleMovement(Vec3* movementDir);
	void handleEatApple(Vec3* lastTailPos,Vec3* lastTailGrid);
	bool hasFloor();
	void handleFall();
	void handleDeath();
	GAME_ENTITY_TYPE getType();
};

