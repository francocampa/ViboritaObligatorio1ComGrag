#pragma once
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <SDL_image.h>
#include "utils.h"
#include <string>


class Button
{
private:
	SDL_Surface* surface;
	GLuint textureId;
	GLuint hoverTextureId;
	SDL_Rect* rectangle;
	bool hover;
public:
	Button();
	virtual void draw();
	virtual void handleClick();
	virtual void handleHover();
	bool isHovering();
	SDL_Rect* getRect();
	bool operator<(Button& other);
};

