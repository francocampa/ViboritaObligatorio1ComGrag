#include "Apple.h"

Apple::Apple(Vec3 position) {
	this->position = position;
	this->angle = 0;
	//this->pivot = { 0.5f + position.x, 0.5f + position.y, 0.433f +position.z};
	this->pivot = { 0,0,0 };
	this->movingUp = true;
	for (int i = 0; i < 12;i++) {
		int module = i % 3;
		int toAdd = 0;
		switch (module) {
		case 0:
			toAdd = position.x;
			printf("\n");
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
	printf("\n\n");
}

void Apple::draw() {
	glPushMatrix();
	glTranslatef(pivot.x, pivot.y, pivot.z);
	glRotatef(this->angle, 0, 1.0, 0);
	drawPyramid(this->pyramid,basePyramidColors,basePyramydIndices);
	glPopMatrix();
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
	
	//this->angle += 0.5f;
}