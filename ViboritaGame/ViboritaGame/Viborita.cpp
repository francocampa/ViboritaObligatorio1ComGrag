#include "Viborita.h"

Viborita::Viborita(Vec3 position, GLfloat colors[24]) {
	for (int i = 0; i < 24; i++) {
		this->viboritaColors[i] = colors[i]; 
	}
	this->cola.x = position.x - 1;
	this->cola.y = position.y;
	this->cola.z = position.z;
	this->positions.head = new posList;
	this->positions.head->next = new posList;
	this->positions.head->next->next = NULL;
	this->positions.head->next->positions = this->cola;//posición inicial de la cola
	this->positions.head->positions = position;
	this->positions.tail = this->positions.head->next;
	this->positions.size = 2;
	this->moving = 0;
	for (int i = 0; i < 24; i++) {
		this->viborita[i] = baseCubeVertices[i];
	}
}

//TODO: Agregar lógica para dibujar el cuerpo de tamaño n.
void Viborita::draw() {
		glPushMatrix();
		glTranslatef(this->positions.head->positions.x, this->positions.head->positions.y, this->positions.head->positions.z);
		drawCube(this->viborita, this->viboritaColors, baseCubeIndices);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(this->cola.x, this->cola.y, this->cola.z);
		drawCube(this->viborita, this->viboritaColors, baseCubeIndices);
		glPopMatrix();
}


//TODO: Ajustar movimiento según la grilla
void Viborita::process(float deltaTime) {
		posList* aux = this->positions.head;
		switch (moving) {
		case 1:
			this->cola = this->positions.head->positions;//la cola tomará la pos. del bloque siguiente
			for (int i = 0; i < this->positions.size; i++) {
				if (aux->positions.y <= this->positions.size) {
					aux->positions.y += 0.5;
					aux = aux->next;
				}
			}
			moving = 0;
			break;
		case 2:
			this->cola = this->positions.head->positions;
			for (int i = 0; i < this->positions.size; i++) {
				if (aux->positions.y - 0.5 >= 0) {
					aux->positions.y -= 0.5;
					aux = aux->next;
				}
			}
			moving = 0;
			break;
		case 3:
			this->cola = this->positions.head->positions;
			for (int i = 0; i < this->positions.size; i++) {
				aux->positions.x += 0.5;
				aux = aux->next;
			}
			moving = 0;
			break;
		case 4:
			this->cola = this->positions.head->positions;
			for (int i = 0; i < this->positions.size; i++) {
				aux->positions.x -= 0.5;
				aux = aux->next;
			}
			moving = 0;
			break;
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
