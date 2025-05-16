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
