#include "Apple.h"

Apple::Apple(Vec3 gridIndexes, Vec3 position) : IGameEntity(gridIndexes,position) {
	this->angle = 0;
	this->movingUp = true;
	for (int i = 0; i < 12;i++) {
		int module = i % 3;
		int toAdd = 0;
		switch (module) {
		case 0:
			toAdd = position.x;
			break;
		case 1:
			toAdd = position.y;
			break;
		case 2:
			toAdd = position.z;
			break;
		}

		this->pyramid[i] = basePyramidVertices[i] + toAdd;
	}
}

void Apple::draw() {

	glPushMatrix();
	glTranslatef(this->pyramid[0] + 0.5f, this->pyramid[1], this->pyramid[2] + 0.5f);
	glScalef(0.2f, 0.2f, 0.2f);
	glColor3f(1, 0.388f, 0.278f);//color rojo de las manzanas
	drawModel(APPLE_MODEL);
	glPopMatrix();
}

GAME_ENTITY_TYPE Apple::getType()
{
	return APPLE;
}

void Apple::process(float deltaTime) {
	float movement = deltaTime * 0.5f;
	if (movingUp) {
		this->pyramid[1] += movement;
		this->pyramid[4] += movement;
		this->pyramid[7] += movement;
		this->pyramid[10] += movement;
	}
	else {
		this->pyramid[1] -= movement;
		this->pyramid[4] -= movement;
		this->pyramid[7] -= movement;
		this->pyramid[10] -= movement;
	}

	if (this->pyramid[10] > position.y+1.5f) {
		movingUp = false;
	}
	else if (this->pyramid[10] < position.y+1.0f) {
		movingUp = true;
	}
	
	this->angle += 0.5f;
}