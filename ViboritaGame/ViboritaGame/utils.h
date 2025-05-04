#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include <cmath>
#include <GL/glu.h>
#include <glm/glm.hpp>

struct Vec3 {
	float x, y, z;
};

float distance(const Vec3& a, const Vec3& b);

void drawCube(GLfloat vertices[], GLfloat colors[], GLubyte indices[]);

extern GLfloat baseCubeVertices[];

extern GLfloat baseCubeColors[];

extern GLubyte baseCubeIndices[];
