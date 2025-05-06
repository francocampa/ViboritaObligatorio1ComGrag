#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <GL/glu.h>
#include "utils.h"
#include <vector>
#include "IGameEntity.h"

class Viborita :
	public IGameEntity
{
private:
	GLfloat viboritaColors[24];
	ViboritaBody body;
<<<<<<< Updated upstream
	Vec3 headDirection;
=======
	Vec3 prevMovement;
	ViboritaPart* prePosition;
>>>>>>> Stashed changes
public:
	Viborita(Vec3 gridPosition,Vec3 position, GLfloat colors[24] );
	void process(float deltaTime);
	void draw();
<<<<<<< Updated upstream
	Vec3* getMovementDirection();
	void handleMovement(Vec3* movementDir);
	void handleEatApple(Vec3* lastTailPos,Vec3* lastTailGrid);
	bool hasFloor();
	void handleFall();
	void handleDeath();
	GAME_ENTITY_TYPE getType();
=======
	ViboritaPart* getHead();
	ViboritaPart* getPreHead();
	void setHead(ViboritaPart*);
	void grow(Vec3 direction);
>>>>>>> Stashed changes
};

