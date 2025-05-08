#include "Button.h"

TTF_Font* Button::font = nullptr;

Button::Button(const char* texturePath, const char* hoverPath, const char* selectedPath, int x, int y, int width, int height, void(*callback)())
{
	hover = false;
	selected = false;

	loadTexture(this->textureId, texturePath);
	loadTexture(this->hoverTextureId, hoverPath);
	loadTexture(this->selectedTextureId, selectedPath);

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;

	this->callback = callback;
	this->strcallback = NULL;
}

Button::Button(const char* texturePath, const char* hoverPath, int x, int y, int width, int height, void (*callback)())
{//Btn con hover
	hover = false;
	selected = false;

	loadTexture(this->textureId, texturePath);
	loadTexture(this->hoverTextureId, hoverPath);
	this->selectedTextureId = NULL;

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;

	this->callback = callback;
	this->strcallback = NULL;
}

Button::Button(const char* texturePath, const char* hoverPath, const char* selectedPath, int x, int y, int width, int height, void(*callback)(std::string arg), std::string arg)
{
	hover = false;
	selected = false;

	loadTexture(this->textureId, texturePath);
	loadTexture(this->hoverTextureId, hoverPath);
	loadTexture(this->selectedTextureId, selectedPath);

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;

	this->callback = NULL;
	this->strcallback = callback;
	this->arg = arg;
}

Button::Button(const char* texturePath, const char* hoverPath, int x, int y, int width, int height, void(*callback)(std::string arg),std::string arg)
{
	hover = false;
	selected = false;

	loadTexture(this->textureId, texturePath);
	loadTexture(this->hoverTextureId, hoverPath);
	this->selectedTextureId = NULL;

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;

	this->callback = NULL;
	this->strcallback = callback;
	this->arg = arg;
}

Button::Button(const char* texturePath, int x, int y, int width, int height, void(*callback)())
{//Btn sin hover
	hover = false;
	selected = false;

	loadTexture(this->textureId, texturePath);
	this->hoverTextureId = NULL;
	this->selectedTextureId = NULL;

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;

	this->callback = callback;
	this->strcallback = NULL;
}

Button::Button(const char* text, int x, int y, int width, int height)
{//Renderizador de texto xdxd
	hover = false;
	selected = false;

	loadTextTexture(this->textureId, text, font);
	this->hoverTextureId = NULL;

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;
	this->callback = NULL;
	this->strcallback = NULL;
}

Button::Button(const char* text, int x, int y, int width, int height, void(*callback)(std::string arg), std::string arg)
{
	hover = false;
	selected = false;

	loadTextTexture(this->textureId, text, font);
	this->hoverTextureId = NULL;

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;
	this->callback = NULL;
	this->strcallback = callback;
	this->arg = arg;
}

void Button::draw()
{
	glBindTexture(GL_TEXTURE_2D, selected ? selectedTextureId : isHovering() ? hoverTextureId : textureId);
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
	if (strcallback != NULL)
		this->strcallback(arg);
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

void Button::setSelected(bool selected)
{
	this->selected = selected;
}

Button::~Button()
{
	glDeleteTextures(1, &textureId);
	if(hoverTextureId != NULL)
		glDeleteTextures(1, &hoverTextureId);
	if(selectedTextureId != NULL)
		glDeleteTextures(1, &selectedTextureId);
}
