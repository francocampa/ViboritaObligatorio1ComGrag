#pragma once
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <SDL_image.h>
#include "utils.h"
#include <string>

//class HudController;

class Button
{
private:
	GLuint textureId;
	GLuint hoverTextureId;
	SDL_Rect* rectangle;
	bool hover;
	void (*callback)();
	static TTF_Font* font;
public:
	Button(const char* texturePath, const char* hoverPath, int x, int y, int width, int height, void (*callback)()); //Button ocn hover
	Button(const char* texturePath, int x, int y, int width, int height, void (*callback)()); //Button sin hover
	Button(const char* texturePath, int x, int y, int width, int height); //Renderiza solo texto
	void draw();
	void handleClick();
	void handleHover();
	bool isHovering();
	void updateText(const char* texturePath); //Only when text rendering
	SDL_Rect* getRect();
	static void setFont(TTF_Font* font);
	~Button();
};

