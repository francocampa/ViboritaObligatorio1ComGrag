#pragma once
#include "IHudElement.h"

class Message : public IHudElement
{
private:
	GLuint textureId;
	float beginProgress;
	float endProgress;
	float age;
	float lifeSpan;
	SDL_Rect* rect;

public:
	Message(GLuint textureId, float lifeSpan, int x, int y);
	void draw();
	void process(float deltaTime);
	BUTTON_TYPE getType();
	SDL_Rect* getRect();
	~Message() {}
};

