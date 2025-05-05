#pragma once
#include "Button.h"

class LevelButton :
    public Button
{
private:
	SDL_Surface* surface;
	GLuint textureId;
	GLuint hoverTextureId;
	SDL_Rect* rectangle;
	bool hover;
public:
	LevelButton(int level);
	virtual void draw();
	virtual void handleClick();
	virtual void handleHover();
	bool isHovering();
	SDL_Rect* getRect();
};

