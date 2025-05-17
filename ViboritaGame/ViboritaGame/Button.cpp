#include "Button.h"

Button::Button()
{
}

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

Button::Button(const char* text, int x, int y)
{//Renderizador de texto xdxd
	hover = false;
	selected = false;
	int width = 0;
	int height = 0;
	loadTextTexture(this->textureId, text, font,width,height);
	this->hoverTextureId = NULL;

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	this->rectangle->w = width;
	this->rectangle->h = height;
	this->callback = NULL;
	this->strcallback = NULL;
}

Button::Button(const char* text, int x, int y, void(*callback)(std::string arg), std::string arg,bool selectable)
{
	this->selectable = selectable;
	textBtn = true;
	hover = false;
	selected = false;
	int width = 0;
	int height = 0;
	loadTextTexture(this->textureId, text, font, width,height);
	this->hoverTextureId = NULL;

	this->rectangle = new SDL_Rect();
	this->rectangle->x = x;
	this->rectangle->y = y;
	
	GLuint id = textureId;
	this->rectangle->w = width;
	this->rectangle->h = height;
	this->callback = NULL;
	this->strcallback = callback;
	this->arg = arg;
}

void Button::draw()
{
	glBindTexture(GL_TEXTURE_2D, selected ? selectedTextureId : hoverTextureId != NULL && isHovering() ? hoverTextureId : textureId);
	glEnable(GL_TEXTURE_2D);
	int yOffset = 0;
	glColor3f(hoverProgress, hoverProgress, hoverProgress);
	yOffset = -rectangle->h * hoverProgress;
	
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(rectangle->x, yOffset + rectangle->y);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(rectangle->x + rectangle->w, yOffset + rectangle->y);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(rectangle->x + rectangle->w, yOffset + rectangle->y + rectangle->h);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(rectangle->x, yOffset + rectangle->y + rectangle->h);
	glEnd();
	glColor3f(0, 0, 0);
	glDisable(GL_TEXTURE_2D);
}

void Button::process(float deltaTime)
{
	if (hover) 
		hoverProgress += hoverProgress < 0.3 ? 2.0f * deltaTime : 0;
	else if(hoverProgress > 0)
		hoverProgress -= 2.0f * deltaTime;
	
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
	return hover;
}

void Button::updateText(const char* newText)
{
	glDeleteTextures(1, &textureId);
	int width = 0;
	int height = 0;
	loadTextTexture(this->textureId, newText, font,width,height);
	this->rectangle->w = width;
	this->rectangle->h = height;
}

SDL_Rect* Button::getRect()
{
	return this->rectangle;
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

BUTTON_TYPE Button::getType()
{
	return BUTTON;
}
