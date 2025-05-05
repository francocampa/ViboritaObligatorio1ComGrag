#include "Viborita.h"

Viborita::Viborita(Vec3 position, GLfloat colors[24]) {
	for (int i = 0; i < 24; i++) {
		this->viboritaColors[i] = colors[i]; 
	}
	Vec3 cola;
	cola.x = position.x - 1;
	cola.y = position.y;
	cola.z = position.z;
	this->positions.head = new posList;
	this->positions.head->next = new posList;
	this->positions.head->next->next = NULL;
	this->positions.head->next->positions = cola;
	this->positions.head->positions = position;
	this->positions.tail = this->positions.head->next;
	this->positions.size = 2;
	this->rotation[0] = 0;
	this->rotation[1] = 1;
	this->rotation[2] = 0;
	this->rotation[3] = 0;
	this->moving = 0;
	for (int i = 0; i < 24; i++) {
		this->viborita[i] = baseCubeVertices[i];
	}
}

void Viborita::draw() {
	posList* aux = this->positions.head;
	while (aux != NULL) {
		glPushMatrix();
		glTranslatef(aux->positions.x, aux->positions.y, aux->positions.z);
		glRotatef(this->rotation[0], this->rotation[1], this->rotation[2], this->rotation[3]);
		drawCube(this->viborita, this->viboritaColors, baseCubeIndices);
		glPopMatrix();
		aux = aux->next;
		
	}
}

void Viborita::process(float deltaTime) {
	while (this->moving != 0) {
		posList* aux = this->positions.head;
		switch (moving) {
		case 1:
			for (int i = 0; i < this->positions.size; i++) {
				aux->positions.x += 0.5f;
				aux = aux->next;
			}
			break;
		case 2:
			for (int i = 0; i < this->positions.size; i++) {
				aux->positions.x -= 0.5f;
				aux = aux->next;
			}
			break;
		case 3:
			for (int i = 0; i < this->positions.size; i++) {
				aux->positions.z += 0.5f;
				aux = aux->next;
			}
			break;
		case 4:
			for (int i = 0; i < this->positions.size; i++) {
				aux->positions.z -= 0.5f;
				aux = aux->next;
			}
			break;
		}
	}
}

void Viborita::setUp() {
	this->moving = 1;
}

void Viborita::setDown() {
	this->moving = 2;
}

void Viborita::setRight() {
	this->moving = 3;
}

void Viborita::setLeft() {
	this->moving = 4;
}

void Viborita::stopMoving() {
	this->moving = 0;
}
