#include "Viborita.h"
#include "GameController.h"

Viborita::Viborita(Vec3 gridIndexes, Vec3 position, GLfloat colors[24]) : IGameEntity(gridIndexes,position) {
	for (int i = 0; i < 24; i++) {
		this->viboritaColors[i] = colors[i]; 
	}

	ViboritaPart* head = new ViboritaPart;
	head->gridIndex = gridIndexes;
	head->position = position;
	head->next = nullptr;

	body.head = head;
	body.tail = head;
	body.size = 1;

	prevMovement = { 0,0,0 };
}

//TODO: Agregar lógica para dibujar el cuerpo de tamaño n.
void Viborita::draw() {
	ViboritaPart* bodyPart = this->body.head;
	while(bodyPart != NULL)
	{
		glPushMatrix();
		glTranslatef(bodyPart->position.x, bodyPart->position.y, bodyPart->position.z);
		drawCube(baseCubeVertices, this->viboritaColors, baseCubeIndices); //Como ya hice el translate dibujo el base cube nada m[as, sino va a estar doblemente corrido
		glPopMatrix();
		bodyPart = bodyPart->next;
	}
}


//TODO: Ajustar movimiento según la grilla
void Viborita::process(float deltaTime) {

	Vec3* movementDir = new Vec3;
	movementDir->x = 0;
	movementDir->y = 0;
	movementDir->z = 0;

	if (GameController::getInstance()->isArrowUp())
		movementDir->z = 1; 
	else if (GameController::getInstance()->isArrowDown())
		movementDir->z = -1;
	else if (GameController::getInstance()->isArrowLeft())
		movementDir->x = 1;
	else if (GameController::getInstance()->isArrowRight())
		movementDir->x = -1;

	if (movementDir->x == 0 && movementDir->y == 0 && movementDir->z == 0) 
		return;
	if (movementDir->x + prevMovement.x == 0 && movementDir->y + prevMovement.y == 0 && movementDir->z + prevMovement.z == 0)
		return;

	prevMovement = { movementDir->x,movementDir->y,movementDir->z };
	Vec3* prevPos = new Vec3;
	prevPos->x = this->body.head->position.x;
	prevPos->y = this->body.head->position.y;
	prevPos->z = this->body.head->position.z;
	Vec3* prevGrid = new Vec3;
	prevGrid->x = this->body.head->gridIndex.x;
	prevGrid->y = this->body.head->gridIndex.y;
	prevGrid->z = this->body.head->gridIndex.z;

	this->body.head->position.x += GameController::getInstance()->TILE_SIZE * movementDir->x;
	this->body.head->position.y += GameController::getInstance()->TILE_SIZE * movementDir->y;
	this->body.head->position.z += GameController::getInstance()->TILE_SIZE * movementDir->z;

	this->body.head->gridIndex.x += movementDir->x;
	this->body.head->gridIndex.y += movementDir->y;
	this->body.head->gridIndex.z += movementDir->z;

	ViboritaPart* aux = this->body.head->next;
	ViboritaPart* tail = this->body.head;
	while (aux != NULL) {
		tail = aux;
		Vec3 auxPos = { aux->position.x,aux->position.y,aux->position.z };
		Vec3 auxGrid = { aux->gridIndex.x,aux->gridIndex.y,aux->gridIndex.z };
		aux->position = { prevPos->x,prevPos->y,prevPos->z };
		aux->gridIndex = { prevGrid->x,prevGrid->y,prevGrid->z };

		prevPos->x = auxPos.x;
		prevPos->y = auxPos.y;
		prevPos->z = auxPos.z;
		prevGrid->x = auxGrid.x;
		prevGrid->y = auxGrid.y;
		prevGrid->z = auxGrid.z;
		aux = aux->next;
	}

	if (GameController::getInstance()->tileHasApple(body.head->gridIndex.x, body.head->gridIndex.y, body.head->gridIndex.z)) {
		GameController::getInstance()->clearTile(body.head->gridIndex.x, body.head->gridIndex.y, body.head->gridIndex.z);
		
		ViboritaPart* newTail = new ViboritaPart;
		newTail->position = { prevPos->x,prevPos->y,prevPos->z };
		newTail->gridIndex = { prevGrid->x,prevGrid->y,prevGrid->z };
		newTail->next = NULL;
		tail->next = newTail;
		this->body.tail = newTail;
		this->body.size++;
	}
}
