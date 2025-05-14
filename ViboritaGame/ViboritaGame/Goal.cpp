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
	//TODO: arreglar giro de la meta
	glPushMatrix();
	glTranslatef(position.x + 0.5, position.y-1.2f, position.z); //TODO sacar estos valores hardcodeados, que sean en base a TILE_SIZE
	glScalef(0.5, 0.5, 0.5);
	//glRotatef(this->angle, 0.5f, 0.5f , 0.5f);
	glRotatef(90, 0, 1, 0);
	glColor3f(0, 0, 0); //color negro
	drawModel(GOAL_MODEL, GameController::getInstance()->getSettings()->hasTextures());
	glColor3f(1, 1, 1); //color negro
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
