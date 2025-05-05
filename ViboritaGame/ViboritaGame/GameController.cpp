#include "GameController.h"

GameController* GameController::instance = NULL;

GameController::GameController() {
	GRID_SIZE = 8;
	TILE_SIZE = 1;
	GRID_OFFSET = GRID_SIZE / 2;
	for (int x = 0; x < GRID_SIZE;x++) {
		for (int y = 0; y < GRID_SIZE;y++) {
			for (int z = 0; z < GRID_SIZE;z++) {
				grid[x][y][z] = NULL;

			}
		}
	}

	GLfloat colores[] = {
		0.20, 0.20, 0.20,
		0.30, 0.30, 0.30,
		0.50, 0.50, 0.50,
		0.70, 0.70, 0.70,
		0.90, 0.90, 0.90,
		0.110, 0.110, 0.110
	};
	Vec3 applePos = { getGridPosition(3),getGridPosition(4),getGridPosition(3) };
	grid[3][4][3] = new Apple(applePos);
	Vec3 viboritaPos = { getGridPosition(5),getGridPosition(4),getGridPosition(5) };
	grid[5][4][5] = new Viborita(viboritaPos, colores);
	Viborita* viborita = (Viborita*)grid[5][4][5];

	if (this->up) {
		viborita->setUp();
	}
	else if (this-> down) {
		viborita->setDown();
	}
	else if (this-> left) {
		viborita->setLeft();
	}
	else if (this-> right) {
		viborita->setRight();
	}
	else {
		viborita->stopMoving();
	}

	for (int x = 2; x < 10;x++) {
		for (int y = 2; y < 4;y++) {
			for (int z = 2; z < 7;z++) {
				Vec3 blockPos = { getGridPosition(x),getGridPosition(y),getGridPosition(z) };
				grid[x][y][z] = new Block(blockPos);
			}
		}
	}
}

GameController* GameController::getInstance() {
	if (instance == NULL)
		instance = new GameController();

	return instance;
}

void GameController::processFrame(float deltaTime) {
	for (int x = 0; x < GRID_SIZE;x++) {
		for (int y = 0; y < GRID_SIZE;y++) {
			for (int z = 0; z < GRID_SIZE;z++) {
				if (grid[x][y][z] != NULL) {
					grid[x][y][z]->process(deltaTime);
					grid[x][y][z]->draw();
				}
			}
		}
	}
}

float GameController::getGridPosition(float a) {
	return a * TILE_SIZE - GRID_OFFSET;
}

void GameController::setUP() {
	this->up = !this->up;
}

void GameController::setDOWN() {
	this->down = !this->down;
}

void GameController::setLEFT() {
	this->left = !this->left;
}

void GameController::setRIGHT() {
	this->right = !this->right;
}