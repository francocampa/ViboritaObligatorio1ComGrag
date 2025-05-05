#include "Button.h"

Button::Button()
{
	bool hover = false;
	
	const char* texture = "./images/SoyUnBoton.png";
	const char* textureHover = "./images/SoyUnBotonHover.png";

	loadTexture(this->textureId,texture);
	loadTexture(this->hoverTextureId,textureHover);

	this->rectangle = new SDL_Rect();
	this->rectangle->x = 200;
	this->rectangle->y = 200;
	this->rectangle->w = 300;
	this->rectangle->h = 100;
}

void Button::draw()
{
	glBindTexture(GL_TEXTURE_2D, isHovering() ? hoverTextureId : textureId); // Use your loaded texture ID
	glEnable(GL_TEXTURE_2D);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(rectangle->x, rectangle->y);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(rectangle->x + rectangle->w, rectangle->y);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(rectangle->x + rectangle->w, rectangle->y + rectangle->h);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(rectangle->x, rectangle->y + rectangle->h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Button::handleClick()
{
}

void Button::handleHover()
{
	hover = !hover;
	printf(hover ? "isHovering\n":"notHovering\n");
}

bool Button::isHovering()
{
	return hover;
}

SDL_Rect* Button::getRect()
{
	return this->rectangle;
}

bool Button::operator<(Button& other){
	return textureId < other.textureId;
}