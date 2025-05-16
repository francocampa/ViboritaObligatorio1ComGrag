#pragma once
#include "utils.h"

class IHudElement
{
protected:
	static TTF_Font* font;

public:
	IHudElement();
	virtual void draw();
	virtual BUTTON_TYPE getType();
	virtual SDL_Rect* getRect();
	static void setFont(TTF_Font* font);
};

