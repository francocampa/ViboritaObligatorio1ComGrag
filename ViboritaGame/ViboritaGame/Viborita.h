#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <GL/glu.h>
#include <iostream>
#include "utils.h"
class Viborita
{
private:
	float position[3];
	float rotation[4]; // angle, x, y, z
	float scale[3];
	float color[3];
	GLuint textureID;
	GLuint vertexArrayID;
	GLuint vertexBufferID;
	GLuint colorBufferID;
	GLuint indexBufferID;
	int numIndices;
	void loadTexture(const char* filePath);
	void createBuffers();
	void drawBuffers();
	void updateBuffers();
public:
	Viborita();
	void process(float deltaTime);
	void draw();
	void setPosition(float x, float y, float z);
	void setRotation(float angle, float x, float y, float z);
	void setScale(float x, float y, float z);
	void setColor(float r, float g, float b);
	~Viborita();
};

