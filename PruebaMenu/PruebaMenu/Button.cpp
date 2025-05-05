#include "Button.h"

Button::Button(const char* texturePath, const char* hoverPath, int x, int y, int width, int height, void (*callback)())
{
	bool hover = false;
	

	loadTexture(this->textureId,texturePath);
	if(hoverPath != NULL)
		loadTexture(this->hoverTextureId,hoverPath);

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;

	this->callback = callback;
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
	this->callback();
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
