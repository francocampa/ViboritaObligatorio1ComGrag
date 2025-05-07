#include "Button.h"

TTF_Font* Button::font = nullptr;

Button::Button(const char* texturePath, const char* hoverPath, int x, int y, int width, int height, void (*callback)())
{//Btn con hover
	bool hover = false;


	loadTexture(this->textureId, texturePath);
	loadTexture(this->hoverTextureId, hoverPath);

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;

	this->callback = callback;
}

Button::Button(const char* texturePath, int x, int y, int width, int height, void(*callback)())
{//Btn sin hover
	bool hover = false;


	loadTexture(this->textureId, texturePath);
	this->hoverTextureId = NULL;

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;

	this->callback = callback;
}

Button::Button(const char* text, int x, int y, int width, int height)
{//Renderizador de texto xdxd
	bool hover = false;

	loadTextTexture(this->textureId, text, font);
	this->hoverTextureId = NULL;

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;
	this->callback = NULL;
}

void Button::draw()
{
	glBindTexture(GL_TEXTURE_2D, isHovering() ? hoverTextureId : textureId);
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
	if(callback != NULL)
		this->callback();
}

void Button::handleHover()
{
	hover = !hover;
}

bool Button::isHovering()
{
	return hoverTextureId != NULL && hover;
}

void Button::updateText(const char* newText)
{
	glDeleteTextures(1, &textureId);
	loadTextTexture(this->textureId, newText, font);
}

SDL_Rect* Button::getRect()
{
	return this->rectangle;
}

void Button::setFont(TTF_Font* font)
{
	Button::font = font;
}

Button::~Button()
{
	glDeleteTextures(1, &textureId);
	if(hoverTextureId != NULL)
		glDeleteTextures(1, &hoverTextureId);
}
