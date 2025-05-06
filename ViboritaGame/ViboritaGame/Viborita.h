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
	Vec3 prevMovement;
public:
	Viborita(Vec3 gridPosition,Vec3 position, GLfloat colors[24] );
	void process(float deltaTime);
	void draw();
	void grow(Vec3 direction);
};

