#include "TextField.h"

void TextField::changeText(std::string newText)
{
	if(textTextureId != NULL)
		glDeleteTextures(1, &textTextureId);
	int width = 0;
	int height = 0;
	loadTextTexture(this->textTextureId, newText.c_str(), font, width, height);
	this->textRect->w = width;
	this->textRect->h = height;
}

TextField::TextField(std::string text, int x, int y, int length, void (*callback)(std::string newValue), std::string initialValue) {
	this->height = 32;
	this->value = initialValue;
	this->textTextureId = NULL;
	this->rect = new SDL_Rect();
	rect->x = x;
	rect->y = y;
	rect->h = height;
	rect->w = length;
	this->textRect = new SDL_Rect();
	textRect->x = x+5;
	textRect->y = y+4;
	textRect->w = 0;
	textRect->h = 0;

	if(initialValue != "")
		changeText(initialValue);

	this->maxValueSize = length / 10;
}

void TextField::draw()
{
	if (textTextureId != NULL) {
		glBindTexture(GL_TEXTURE_2D, textTextureId);
		glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		//Renderizo el texto

		glTexCoord2f(0.0f, 0.0f); glVertex2i(textRect->x, textRect->y);
		glTexCoord2f(1.0f, 0.0f); glVertex2i(textRect->x + textRect->w, textRect->y);
		glTexCoord2f(1.0f, 1.0f); glVertex2i(textRect->x + textRect->w, textRect->y + textRect->h);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(textRect->x, textRect->y + textRect->h);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	glBegin(GL_QUADS);
		//Renderizo el rectangulo del input
		glColor3f(0.8f, 0.8f, 0.8f);
		glVertex2i(rect->x, rect->y);
		glVertex2i(rect->x + rect->w, rect->y);
		glVertex2i(rect->x + rect->w, rect->y + rect->h);
		glVertex2i(rect->x, rect->y + rect->h);
		glColor3f(1,1,1);
	glEnd();


}

void TextField::process()
{
	if (!selected || keyPressed == "")
		return;
	
	if (keyPressed == "ENTER") {
		clickOutside();
	}else if (keyPressed == "BACKSPACE" ) {
		if (this->value.length() > 0) {
			this->value = this->value.substr(0, this->value.length() - 1);
			if (value == "") {
				glDeleteTextures(1, &textTextureId);
				textTextureId = NULL;
			}
			else
				changeText(this->value);
		}
	}else if(this->value.length() < maxValueSize) {
		this->value += keyPressed;
		changeText(this->value);
	}
}

BUTTON_TYPE TextField::getType()
{
	return TEXTFIELD;
}

SDL_Rect* TextField::getRect()
{
	return rect;
}

void TextField::click(Vec2 mousePos)
{
	this->selected = true; //TODO: agregar que use la mouse pos para calcular el [indice del string en el que va a seguir escribiendo
}

void TextField::clickOutside()
{
	this->selected = false;
}

void TextField::setKeyPressed(std::string key)
{
	this->keyPressed = key;
}



