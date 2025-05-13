#include "Slider.h"

Slider::Slider(std::string text, int x, int y, int length, float min, float max, void(*callback)(float newValue),float initialValue)
{
	this->girth = 20;

	this->length = length;
	this->progressLine = new SDL_Rect();
	progressLine->x = x;
	progressLine->y = y;
	progressLine->w = length;
	progressLine->h = girth;
	
	this->value = initialValue;
	this->min = min;
	this->max = max;
	this->selector = new SDL_Rect();
	float xProgress = (value-min) / (max - min);
	selector->x = x + (length-girth)*xProgress;
	selector->y = y-girth/2;
	selector->w = girth;
	selector->h = girth*2;
	this->callback = callback;
}

void Slider::draw()
{
	glBegin(GL_QUADS);
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2i(selector->x, selector->y);
	glVertex2i(selector->x + selector->w, selector->y);
	glVertex2i(selector->x + selector->w, selector->y + selector->h);
	glVertex2i(selector->x, selector->y + selector->h);
	glColor3f(1,1,1);
	glVertex2i(progressLine->x, progressLine->y);
	glVertex2i(progressLine->x + progressLine->w, progressLine->y);
	glVertex2i(progressLine->x + progressLine->w, progressLine->y + progressLine->h);
	glVertex2i(progressLine->x, progressLine->y + progressLine->h);
	glColor3f(1, 1, 1);
	glEnd();
}

void Slider::mouseDown(Vec2 mousePos)
{
	this->movingSelector = true;
}

void Slider::mouseUp()
{
	this->movingSelector = false;
}

void Slider::process(Vec2 mousePos)
{
	if (!movingSelector)
		return;

	float newProgress = (float)(mousePos.x - progressLine->x)/(float)(length-girth);

	if (newProgress > 1)
		newProgress = 1;
	else if (newProgress < 0)
		newProgress = 0;

	selector->x = progressLine->x + (length-girth) * newProgress;
	this->value = min + (max - min) * newProgress;
	callback(this->value);
}

SDL_Rect* Slider::getRect()
{
	return progressLine;
}

BUTTON_TYPE Slider::getType()
{
	return SLIDER;
}
