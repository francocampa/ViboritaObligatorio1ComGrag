#pragma once
#include "utils.h"

class IHudElement
{
public:
	IHudElement();
	virtual void draw();
	virtual BUTTON_TYPE getType();
	virtual SDL_Rect* getRect();
};

