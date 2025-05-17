#include "IHudElement.h"

TTF_Font* IHudElement::font = nullptr;

IHudElement::IHudElement()
{
}

void IHudElement::draw()
{
}

BUTTON_TYPE IHudElement::getType()
{
	return BUTTON_TYPE();
}

SDL_Rect* IHudElement::getRect()
{
	return nullptr;
}

void IHudElement::setFont(TTF_Font* font)
{
	IHudElement::font = font;
}

void IHudElement::goBackTo3d()
{
	glDisable(GL_BLEND);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void IHudElement::goBackTo2d()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 640, 480, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
}
