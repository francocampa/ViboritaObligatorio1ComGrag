#include "IGameEntity.h"

void IGameEntity::draw() {

}

IGameEntity::IGameEntity(Vec3 gridIndexes, Vec3 position)
{
	this->gridIndexes = gridIndexes;
	this->position = position;
}

void IGameEntity::process(float deltaTime) {

}