#include "Block.h"

Block::Block(Vec3 gridIndexes, Vec3 position) : IGameEntity(gridIndexes,position) {
	for (int i = 0; i < 24;i++) {
		int module = i % 3;
		int toAdd = 0;
		switch (module) {
		case 0:
			toAdd = position.x;
			printf("\n");
			break;
		case 1:
			toAdd = position.y;
			break;
		case 2:
			toAdd = position.z;
			break;
		}

		this->cube[i] = baseCubeVertices[i] + toAdd;
		printf("%f, ", this->cube[i]);
	}
	printf("\n\n");
}

void Block::draw() {
	drawCube(this->cube, baseCubeColors, baseCubeIndices);
}

void Block::process(float deltaTime) {

}