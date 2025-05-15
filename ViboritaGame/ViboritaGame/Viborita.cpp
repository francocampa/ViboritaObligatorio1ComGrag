#include "Viborita.h"
#include "GameController.h"

Viborita::Viborita(Vec3 gridIndexes, Vec3 position, GLfloat colors[24]) : IGameEntity(gridIndexes,position) {
	for (int i = 0; i < 24; i++) {
		this->viboritaColors[i] = colors[i]; 
	}

	ViboritaPart* head = new ViboritaPart;
	head->gridIndex = gridIndexes;
	head->position = position;
	head->dirToFront = { 0,0,1 };
	head->next = nullptr;
	this->falling = 0;
	this->fallen = false;

	body.head = head;
	body.tail = head;
	body.size = 1;

	headDirection = { 0,0,0 };
}

void Viborita::setGameContext(GamePlay* context)
{
	this->gameContext = context;
}

float angle = 90;

void handlePartRotation(Vec3 dir,Vec3 rf) { //rf = rotationFactor 
	if (dir.y == -1) {
		if (dir.x == 1) {
			glRotatef(90, 0, 1, 0); //(-1,0,0)
			glRotatef(90, 1, 0, 0); //(0,-1,1)
		}
		else if (dir.x == -1) {
			glRotatef(90, 0, -1, 0); //(1,0,0)
			glRotatef(90, 1, 0, 0); //(0,-1,1)
		}
		else if (dir.z == -1) {
			glRotatef(180, 0, 1, 0); //(0,0,-1)
			glRotatef(90, 1, 0, 0); //(0,-1,1)
		}
		else if (dir.z == 1) {
			glRotatef(90, 1, 0, 0); //(0,-1,1)
		}
	}
	else if (dir.y == 1) {
		if (dir.x == 1) {
			glRotatef(90, 0, 1, 0); //(-1,0,0)
			glRotatef(90, -1, 0, 0);
			if (rf.y == -1)
				glRotatef(45, -1, 0, 0); //(0,0,-1)
			if (rf.y == 1)
				glRotatef(45, 1, 0, 0); //(0,0,-1)
		}
		else if (dir.x == -1) {
			glRotatef(90, 0, -1, 0); //(1,0,0)
			glRotatef(90, -1, 0, 0);
			if (rf.y == -1)
				glRotatef(45, -1, 0, 0); //(0,0,-1)
			if (rf.y == 1)
				glRotatef(45, 1, 0, 0); //(0,0,-1)
		}
		else if (dir.z == -1) {
			glRotatef(180, 0, 1, 0); //(0,1,-1)
			glRotatef(90, -1, 0, 0); 
			if (rf.y == -1)
				glRotatef(45, -1, 0, 0); //(0,0,-1)
			if (rf.y == 1)
				glRotatef(45, 1, 0, 0); //(0,0,-1)
		}
		else if (dir.z == 1) {
			glRotatef(90, -1, 0, 0); //(0,1,1)
			if (rf.y == 1)
				glRotatef(45, 1, 0, 0); //(0,0,-1)
			if (rf.y == -1)
				glRotatef(45, -1, 0, 0); //(0,0,-1)
		}
	}
	else {
		if (dir.x == 1) {
			glRotatef(90, 0, 1, 0); //(1,0,0)
			if (rf.z == 1)
				glRotatef(45, 0, 1, 0); //(0,0,-1)
			if (rf.z == -1)
				glRotatef(45, 0, -1, 0); //(0,0,-1)
		}
		else if (dir.x == -1) {
			glRotatef(90, 0, -1, 0); //(-1,0,0)
			if (rf.z == 1)
				glRotatef(45, 0, -1, 0); //(0,0,-1)
			if (rf.z == -1)
				glRotatef(45, 0, 1, 0); //(0,0,-1)
		}
		else if (dir.z == -1) {
			glRotatef(180, 0, 1, 0); //(0,0,-1)

			if (rf.x == -1)
				glRotatef(45, 0, -1, 0); //(0,0,-1)
			if (rf.x == 1)
				glRotatef(45, 0, 1, 0); //(0,0,-1)
		}
		else if (dir.z == 1) {
			if(rf.x == -1)
				glRotatef(45, 0, 1, 0); //(0,0,-1)
			if (rf.x == 1)
				glRotatef(45, 0, -1, 0); //(0,0,-1)
			//glRotatef(180, 0, 0, 0); //(0,0,1)
		}
	}


}

void Viborita::draw() {
	float TILE_SIZE = GameController::getInstance()->TILE_SIZE;
	ViboritaPart* bodyPart = this->body.head;
	ViboritaPart* frontPart = NULL;
	Vec3 cero = { 0,0,0 };
	Vec3 headColor = { 0.0f, 0.25f, 0.3f };
	Vec3 viboritaColor = { 0.0f, 0.40f, 0.0f };
	glColor3f(0.0f, 0.50f, 0.0f);

	while(bodyPart != NULL)
	{
		glPushMatrix();
		glTranslatef(bodyPart->position.x, bodyPart->position.y - (TILE_SIZE * this->falling), bodyPart->position.z);

		glTranslatef(TILE_SIZE/2,0,TILE_SIZE/2);

		glScalef(0.5f, 0.5f, 0.5f);
		if (bodyPart == this->body.head) {
			handlePartRotation(this->body.head->dirToFront, cero);
			drawModel(WORM_HEAD_MODEL,GameController::getInstance()->getSettings()->hasTextures());
		}
		else if (bodyPart == this->body.tail) {
			handlePartRotation(this->body.tail->dirToFront, cero);
			drawModel(WORM_TAIL_MODEL, GameController::getInstance()->getSettings()->hasTextures());
		}else {
			Vec3 dirToBack = subtractV3(bodyPart->gridIndex, { bodyPart->next->gridIndex.x,bodyPart->next->gridIndex.y,bodyPart->next->gridIndex.z });
			printf("%f,%f,%f \n", dirToBack.x, dirToBack.y, dirToBack.z);
			//printf("%f,%f,%f - ", frontPart->gridIndex.x, frontPart->gridIndex.y, frontPart->gridIndex.z);
			//printf("%f,%f,%f \n", bodyPart->next->gridIndex.x, bodyPart->next->gridIndex.y, bodyPart->next->gridIndex.z);
			Vec3 verticalDirToBack = { bodyPart->dirToFront.x, dirToBack.y,  bodyPart->dirToFront.z };
			dirToBack = dirToBack.y != 0 ? verticalDirToBack : dirToBack;
			//printf("%f,%f,%f | ", bodyPart->dirToFront.x, bodyPart->dirToFront.y, bodyPart->dirToFront.z);
			handlePartRotation(bodyPart->dirToFront,subtractV3(bodyPart->dirToFront, dirToBack));
			drawModel(WORM_BODY_MODEL, GameController::getInstance()->getSettings()->hasTextures());
		}
	/*	
		glColor3f(viboritaColors[0], viboritaColors[1], viboritaColors[2]);
		drawCubeWithNormals(this->body.head == bodyPart ? headColor : viboritaColor, GameController::getInstance()->getSettings()->hasTextures());
		}*/
		
		glPopMatrix();
		frontPart = bodyPart;
		bodyPart = bodyPart->next;	
	}
	if (this->falling >= 1) {
		this->falling = 0;
	}
	glColor3f(1, 1, 1);
}

Vec3* Viborita::getMovementDirection()
{
	Vec3* movementDir = new Vec3;
	movementDir->x = 0;
	movementDir->y = 0;
	movementDir->z = 0;

	if (GameController::getInstance()->isArrowUp())
	{
		movementDir->z = 1;
		this->body.head->dirToFront = { 0,0,1 };
	}
	else if (GameController::getInstance()->isArrowDown())
	{
		movementDir->z = -1;
		this->body.head->dirToFront = { 0,0,-1 };
	}
	else if (GameController::getInstance()->isArrowLeft())
	{
		movementDir->x = 1;
		this->body.head->dirToFront = { 1,0,0 };
	}
	else if (GameController::getInstance()->isArrowRight())
	{
		movementDir->x = -1;
		this->body.head->dirToFront = { -1,0,0 };
	}
	else if (GameController::getInstance()->isZKey())
	{
		movementDir->y = 1;
		float x = this->body.head->dirToFront.x;
		float z = this->body.head->dirToFront.z;
		this->body.head->dirToFront = { x,1,z };
	}
	else if (GameController::getInstance()->isXKey())
	{
		float x = this->body.head->dirToFront.x;
		float z = this->body.head->dirToFront.z;
		this->body.head->dirToFront = { x,-1,z };
		movementDir->y = -1;
	}
	return movementDir;
}

bool Viborita::handleMovement(Vec3* movementDir) {
	Vec3 nextGridIndex = { this->body.head->gridIndex.x + movementDir->x,this->body.head->gridIndex.y + movementDir->y,this->body.head->gridIndex.z + movementDir->z };

	if (!gameContext->validTile(nextGridIndex)
		|| gameContext->hasSolidBlock(nextGridIndex)) //Se choca con un bloque
		return false;
	if (gameContext->hasViborita(nextGridIndex)) {
		handleDeath();
		return false;
	}
	if (gameContext->hasGoal(nextGridIndex)) {
		gameContext->beatLevel();
		return false;
	}

	headDirection = { movementDir->x,movementDir->y,movementDir->z };

	Vec3* prevPos = getVec3FromVec3(this->body.head->position);
	Vec3* prevGrid = getVec3FromVec3(this->body.head->gridIndex);

	this->body.head->position.x += GameController::getInstance()->TILE_SIZE * movementDir->x;
	this->body.head->position.y += GameController::getInstance()->TILE_SIZE * movementDir->y;
	this->body.head->position.z += GameController::getInstance()->TILE_SIZE * movementDir->z;
	gameContext->clearTile(this->body.head->gridIndex);
	this->body.head->gridIndex = nextGridIndex;

	ViboritaPart* aux = this->body.head->next;
	ViboritaPart* prev = this->body.head;
	while (aux != NULL) {
		Vec3 auxPos = { aux->position.x,aux->position.y,aux->position.z };
		Vec3 auxGrid = { aux->gridIndex.x,aux->gridIndex.y,aux->gridIndex.z };
		
		aux->position = { prevPos->x,prevPos->y,prevPos->z };
		gameContext->clearTile(aux->gridIndex);
		aux->gridIndex = { prevGrid->x,prevGrid->y,prevGrid->z };
		gameContext->addViborita(aux->gridIndex);

		Vec3 newDir = subtractV3({ prev->gridIndex.x,prev->gridIndex.y,prev->gridIndex.z }, aux->gridIndex);
		Vec3 newVerticalDir = { aux->dirToFront.x, newDir.y, aux->dirToFront.z };
		aux->dirToFront = newDir.y != 0 ? newVerticalDir : newDir;

		prevPos = getVec3FromVec3(auxPos);
		prevGrid = getVec3FromVec3(auxGrid);
		prev = aux;
		aux = aux->next;
	}
	return true;
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
	gameContext->addViborita(newTail->gridIndex);
	gameContext->ateApple();
}

bool Viborita::hasFloor()
{
	ViboritaPart* aux = this->body.head;
	while (aux != NULL)
	{
		Vec3 indexUnderPart = { aux->gridIndex.x,aux->gridIndex.y - 1,aux->gridIndex.z };
		if (gameContext->hasSolidBlock(indexUnderPart))
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
		gameContext->clearTile(aux->gridIndex);
		Vec3 positionUnderPart = { aux->position.x,aux->position.y - GameController::getInstance()->TILE_SIZE,aux->position.z};
		Vec3 indexUnderPart = { aux->gridIndex.x,aux->gridIndex.y - 1,aux->gridIndex.z };
		aux->position = positionUnderPart;
		aux->gridIndex = indexUnderPart;
		if (indexUnderPart.y < minY)
			minY = indexUnderPart.y;

		if (gameContext->hasGoal(aux->gridIndex)) { //Si te caes arriba de la meta xd
			gameContext->beatLevel();
			return;
		}

		gameContext->addViborita(aux->gridIndex);
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
	gameContext->resetLevel();
}

Viborita* Viborita::deepCopy()
{
	Viborita* copy = new Viborita(body.head->gridIndex,body.head->position,viboritaColors);
	ViboritaPart* aux = body.head->next;
	while (aux != NULL)
	{
		copy->addTail(aux->gridIndex);
		aux = aux->next;
	}
	return copy;
}

GAME_ENTITY_TYPE Viborita::getType()
{
	return VIBORITA;
}

void Viborita::process(float deltaTime) {

	if (!this->fallen && !hasFloor()) {
		this->falling = 0.00000001f;
		this->fallen = true;
		return;
	}

	if (this->fallen && falling != 0) {
		this->falling += this->falling;
		return;
	}
	else {
		this->fallen = false;
	}

	if (!hasFloor()) {
		handleFall();
		return;
	}

	Vec3* movementDir = this->getMovementDirection();

	if (movementDir->x == 0 && movementDir->y == 0 && movementDir->z == 0)  //The user didn't press a movement key
		return;
	if (movementDir->x + headDirection.x == 0 && movementDir->y + headDirection.y == 0 && movementDir->z + headDirection.z == 0) //The user tried to move in the opossite direction
		return;

	Vec3* oldTailPos = getVec3FromVec3(this->body.tail->position);
	Vec3* oldTailGrid = getVec3FromVec3(this->body.tail->gridIndex);

	bool moved = this->handleMovement(movementDir);

	if (moved) {
		if (gameContext->tileHasApple(body.head->gridIndex))
			this->handleEatApple(oldTailPos, oldTailGrid);

		gameContext->addViborita(this->body.head->gridIndex);
	}
}

ViboritaPart* Viborita::getHead() {
	return this->body.head;
}

int Viborita::getSize() {
	return this->body.size;
}

void Viborita::setHead() {
	if (this->body.head != NULL) {
		ViboritaPart* aux = this->body.head;
		this->body.head = this->body.head->next;
		if (this->body.head != NULL) {
			this->body.head->gridIndex = aux->gridIndex;
			this->body.head->position = this->body.head->position;
			this->body.size--;
		}
		delete aux;
	}
	else {
		std::cout << "No hay partes en el cuerpo de la viborita" << std::endl;
	}
}

void Viborita::addTail(Vec3 gridIndex)
{
	ViboritaPart* newTail = new ViboritaPart();
	newTail->next = NULL;
	newTail->gridIndex = gridIndex;
	newTail->position = { GameController::getInstance()->getGridPosition(gridIndex.x),GameController::getInstance()->getGridPosition(gridIndex.y) ,GameController::getInstance()->getGridPosition(gridIndex.z) };

	this->body.tail->next = newTail;
	this->body.tail = newTail;
	this->body.size++;
}

void Viborita::removeBodyFromGridIndex(int x, int y, int z) {
	ViboritaPart* prev = this->body.head;
	ViboritaPart* aux = this->body.head->next;
	bool removeBody = false;

	if (prev->gridIndex.x == x && prev->gridIndex.z == z && prev->gridIndex.y == y) {
		removeBody = true;
		this->body.head = NULL;
		prev->next = NULL;
	}
	while (aux != NULL)
	{
		if (removeBody) {
			this->body.size--;
			//delete prev; TODO: agregar esto sin que crashee
		}
		if (aux->gridIndex.x == x && aux->gridIndex.z == z && aux->gridIndex.y == y){
			removeBody = true;
			prev->next = NULL;
			this->body.tail = prev;
		}		
		prev = aux;
		aux = aux->next;
	}
	if (removeBody) {
		this->body.size--;
		//delete prev; TODO: agregar esto sin que crashee
	}
}


void Viborita::loadInGrid()
{
	ViboritaPart* aux = body.head;
	while (aux != NULL)
	{
		gameContext->addViborita(aux->gridIndex);
		aux = aux->next;
	}
}
