#include "Goal.h"
#include "GameController.h"

Goal::Goal(Vec3 gridIndexes, Vec3 position) : IGameEntity(gridIndexes, position)
{
	this->position = position;
	this->gridIndex = gridIndexes;
	this->angle = 0.0f;
	this->angle += 0.05f;
}

void Goal::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y + 0.5f, position.z);
	glRotatef(this->angle, 0.5f, 0.5f , 0.5f);
	drawCube(baseCubeVertices, baseCubeColors, baseCubeIndices);
	glPopMatrix();
}

GAME_ENTITY_TYPE Goal::getType()
{
	return GOAL;
}

void Goal::process(float deltaTime){  
	this->angle = this->angle + 20.0f * deltaTime; 
	/*Viborita* body = GameController::getInstance()->getGamePlay()->getViborita();  
	if (body->getHead() != NULL && body->getHead()->gridIndex == gridIndex) {  
		body->setHead();
		if (body->getSize() == 0) {
			GameController::getInstance()->getGamePlay()->beatLevel();
		}
	}  */
}
