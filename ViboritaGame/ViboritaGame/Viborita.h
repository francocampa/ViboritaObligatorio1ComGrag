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
	float rotation[4]; // angle, x, y, z
	GLfloat viborita[24];
	GLfloat viboritaColors[24];
	header positions;
	int moving;
	Vec3 cola;
public:
	Viborita(Vec3, GLfloat colors[24] );
	void process(float deltaTime);
	void draw();
	void setUp();
	void setDown();
	void setLeft();
	void setRight();
	void stopMoving();
	~Viborita();
};

