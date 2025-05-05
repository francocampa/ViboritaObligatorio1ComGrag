#pragma once
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <SDL_image.h>

struct Vec2 {
	int x, y;
};

void loadTexture(GLuint &textureId, const char* path);