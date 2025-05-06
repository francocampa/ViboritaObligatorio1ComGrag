#include "Goal.h"
#include "GameController.h"

Goal::Goal(Vec3 gridIndexes, Vec3 position) : IGameEntity(gridIndexes, position)
{
	this->position = position;
	this->angle = 0;
}

void Goal::draw()
{
	glPushMatrix();
	glTranslatef(position.x, position.y + 0.5f, position.z);
	glRotatef(this->angle, 0.5f, 0.5f , 0.5f);
	drawCube(baseCubeVertices, baseCubeColors, baseCubeIndices);
	glPopMatrix();
}

void Goal::process(float deltaTime)  
{  
	this->angle += 0.05f;  
	Viborita* body = GameController::getInstance()->getViborita();  
	Vec3 goalGridIndex = { 2,4,2 };  
	if (body->getHead()->gridIndex == goalGridIndex) {  
		body->setHead(body->getPreHead());
	}  
}
