#include "Message.h"

Message::Message(GLuint textureId, float lifeSpan, int x, int y)
{
}

void Message::draw()
{
}

void Message::process(float deltaTime)
{
}

BUTTON_TYPE Message::getType()
{
	return MESSAGE;
}

SDL_Rect* Message::getRect()
{
	return nullptr;
}
