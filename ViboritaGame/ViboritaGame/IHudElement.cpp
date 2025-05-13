#include "IHudElement.h"

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
