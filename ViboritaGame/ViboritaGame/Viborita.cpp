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
	head->prePosition = nullptr;

	body.head = head;
	body.tail = head;
	body.size = 1;

	headDirection = { 0,0,0 };
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

Vec3* Viborita::getMovementDirection()
{
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
	return movementDir;
}

void Viborita::handleMovement(Vec3* movementDir) {
	Vec3 nextGridIndex = { this->body.head->gridIndex.x + movementDir->x,this->body.head->gridIndex.y += movementDir->y,this->body.head->gridIndex.z + movementDir->z };

	if (!GameController::getInstance()->validTile(nextGridIndex) 
		|| GameController::getInstance()->hasSolidBlock(nextGridIndex)) //Se choca con un bloque
		return;
	if (GameController::getInstance()->hasViborita(nextGridIndex)) {
		handleDeath();
		return;
	}

	Vec3* prevPos = getVec3FromVec3(this->body.head->position);
	Vec3* prevGrid = getVec3FromVec3(this->body.head->gridIndex);

	this->body.head->position.x += GameController::getInstance()->TILE_SIZE * movementDir->x;
	this->body.head->position.y += GameController::getInstance()->TILE_SIZE * movementDir->y;
	this->body.head->position.z += GameController::getInstance()->TILE_SIZE * movementDir->z;
	GameController::getInstance()->clearTile(this->body.head->gridIndex);
	this->body.head->gridIndex = nextGridIndex;

	ViboritaPart* aux = this->body.head->next;
<<<<<<< Updated upstream
=======
	ViboritaPart* tail = this->body.head;
	this->body.head->prePosition = this->body.tail;
>>>>>>> Stashed changes
	while (aux != NULL) {
		Vec3 auxPos = { aux->position.x,aux->position.y,aux->position.z };
		Vec3 auxGrid = { aux->gridIndex.x,aux->gridIndex.y,aux->gridIndex.z };
		aux->position = { prevPos->x,prevPos->y,prevPos->z };
		GameController::getInstance()->clearTile(aux->gridIndex);
		aux->gridIndex = { prevGrid->x,prevGrid->y,prevGrid->z };
		GameController::getInstance()->addViborita(aux->gridIndex);

		prevPos = getVec3FromVec3(auxPos);
		prevGrid = getVec3FromVec3(auxGrid);
		aux = aux->next;
	}
}

void Viborita::handleEatApple(Vec3* lastTailPos, Vec3* lastTailGrid)
{
	ViboritaPart* newTail = new ViboritaPart;
	newTail->position = { lastTailPos->x,lastTailPos->y,lastTailPos->z };
	newTail->gridIndex = { lastTailGrid->x,lastTailGrid->y,lastTailGrid->z };
	newTail->next = NULL;
	this->body.tail->next = newTail;
	this->body.tail = newTail;
	this->body.size++;
	GameController::getInstance()->addViborita(newTail->gridIndex);
}

bool Viborita::hasFloor()
{
	ViboritaPart* aux = this->body.head;
	while (aux != NULL)
	{
		Vec3 indexUnderPart = { aux->gridIndex.x,aux->gridIndex.y - 1,aux->gridIndex.z };
		if (GameController::getInstance()->hasSolidBlock(indexUnderPart))
			return true;
		aux = aux->next;
	}
	return false;
}

void Viborita::handleFall()
{
	ViboritaPart* aux = this->body.head;
	int minY = GameController::getInstance()->GRID_SIZE + 1;
	while (aux != NULL)
	{
		GameController::getInstance()->clearTile(aux->gridIndex);
		Vec3 positionUnderPart = { aux->position.x,aux->position.y - GameController::getInstance()->TILE_SIZE,aux->position.z};
		Vec3 indexUnderPart = { aux->gridIndex.x,aux->gridIndex.y - 1,aux->gridIndex.z };
		aux->position = positionUnderPart;
		aux->gridIndex = indexUnderPart;
		if (indexUnderPart.y < minY)
			minY = indexUnderPart.y;
		GameController::getInstance()->addViborita(aux->gridIndex);
		aux = aux->next;
	}
	if (minY <= 0)
		handleDeath();
}

void Viborita::handleDeath()
{
	/*ViboritaPart* aux = this->body.head;
	while (aux != NULL)
	{
		GameController::getInstance()->clearTile(aux->gridIndex);
		ViboritaPart* toDelete = aux;
		aux = aux->next;
		delete toDelete;
	}

	delete this;*/
}

GAME_ENTITY_TYPE Viborita::getType()
{
	return VIBORITA;
}

void Viborita::process(float deltaTime) {

	if (!hasFloor()) {
		handleFall();
		return;
	}


	Vec3* movementDir = this->getMovementDirection();

	if (movementDir->x == 0 && movementDir->y == 0 && movementDir->z == 0)  //The user didn't press a movement key
		return;
	if (movementDir->x + headDirection.x == 0 && movementDir->y + headDirection.y == 0 && movementDir->z + headDirection.z == 0) //The user tried to move in the opossite direction
		return;

	headDirection = { movementDir->x,movementDir->y,movementDir->z };
	
	Vec3* oldTailPos = getVec3FromVec3(this->body.tail->position);
	Vec3* oldTailGrid = getVec3FromVec3(this->body.tail->gridIndex);

	this->handleMovement(movementDir);

	if (GameController::getInstance()->tileHasApple(body.head->gridIndex))
		this->handleEatApple(oldTailPos,oldTailGrid);

	GameController::getInstance()->addViborita(this->body.head->gridIndex);
}

ViboritaPart* Viborita::getHead() {
	return this->body.head;
}

void Viborita::setHead(ViboritaPart* newHead) {
	ViboritaPart* aux = this->body.head;
	this->body.head = newHead;
	this->body.size--;
	delete aux;
}

ViboritaPart* Viborita::getPreHead() {
	return this->body.head->prePosition;
}
