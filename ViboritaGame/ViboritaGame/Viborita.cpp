#include "Viborita.h"

Viborita::Viborita(Vec3 position, GLfloat colors[24]) {
this->position = position;
for (int i = 0; i < 24; i++) {
	this->viboritaColors[i] = colors[i]; 
}
this->rotation[0] = 0;
this->rotation[1] = 1;
this->rotation[2] = 0;
this->rotation[3] = 0;
for (int i = 0; i < 24; i++) {
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
	this->viborita[i] = baseCubeVertices[i] + toAdd;
}
}

void Viborita::draw() {
glPushMatrix();
glTranslatef(this->position.x, this->position.y, this->position.z);
glRotatef(this->rotation[0], this->rotation[1], this->rotation[2], this->rotation[3]);
drawCube(this->viborita, this->viboritaColors, baseCubeIndices);
glPopMatrix();
}

void Viborita::process(float deltaTime) {
}
