#include "PeaksApple.h"

PeaksApple::PeaksApple(Vec3 gridIndexes, Vec3 position) : IGameEntity(gridIndexes, position)
{
	this->position = position;
	this->gridIndex = gridIndexes;
}

void PeaksApple::process(float deltaTime)
{
}

void PeaksApple::draw()
{
	glPushMatrix();
	glScalef(0.2f, 0.2f, 0.2f);
	glTranslatef(position.x + 0.5f, position.y + 0.5f, position.z + 0.5f);
	drawModel(PEAKS_APPLE_MODEL, false);
	glPopMatrix();
}

GAME_ENTITY_TYPE PeaksApple::getType() {
	return PEAKS_APPLE;
}