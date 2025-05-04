#include "Button.h"

Button::Button()
{
	bool hover = false;
	SDL_Surface* surface = IMG_Load("SoyUnBoton.png");

	glGenTextures(1, &this->textureId);
	glBindTexture(GL_TEXTURE_2D, this->textureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

	// Set texture parameters (optional but recommended)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_FreeSurface(surface);

	this->rectangle.x = 200;
	this->rectangle.y = 200;
	this->rectangle.w = 300;
	this->rectangle.h = 100;
}

void Button::draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId); // Use your loaded texture ID

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(rectangle.x, rectangle.y);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(rectangle.x + rectangle.w, rectangle.y);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(rectangle.x + rectangle.w, rectangle.y + rectangle.h);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(rectangle.x, rectangle.y + rectangle.h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Button::handleClick()
{
}

void Button::handleHover()
{
	hover != hover;
}

bool Button::isHovering()
{
	return hover;
}

bool Button::operator<(Button& other){
	return textureId < other.textureId;
}