#include "Block.h"

Block::Block(Vec3 gridIndexes, Vec3 position) : IGameEntity(gridIndexes,position) {
	for (int i = 0; i < 24;i++) {
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

		this->cube[i] = baseCubeVertices[i] + toAdd;
	}
}

void Block::draw() {
	drawCube(this->cube, baseCubeColors, baseCubeIndices);
}

GAME_ENTITY_TYPE Block::getType()
{
	return BLOCK;
}

void Block::process(float deltaTime) {

}