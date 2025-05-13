#include "Slider.h"

Slider::Slider(std::string text, int x, int y, int length, float min, float max, void(*callback)(float newValue))
{

}

void Slider::draw()
{
}

void Slider::mouseDown(Vec2 mousePos)
{
}

void Slider::mouseUp()
{
}

void Slider::process(Vec2 mousePos)
{
}

SDL_Rect* Slider::getRect()
{
	return progressLine;
}

BUTTON_TYPE Slider::getType()
{
	return SLIDER;
}
