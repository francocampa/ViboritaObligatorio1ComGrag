#pragma once
#include "IHudElement.h"

class TextField : public IHudElement
{
private:
	int height;
	SDL_Rect* rect;
	SDL_Rect* indicator;
	SDL_Rect* textRect;
	bool selected;
	GLuint textTextureId;
	std::string keyPressed;
	std::string value;
	int maxValueSize;

	void changeText(std::string newText);
public:
	static TTF_Font* font;
	TextField(std::string text,int x,int y,int length, void (*callback)(std::string newValue), std::string initialValue);
	void draw();
	void process();
	BUTTON_TYPE getType();
	SDL_Rect* getRect();

	void click(Vec2 mousePos);
	void clickOutside();
	void setKeyPressed(std::string key);
};

