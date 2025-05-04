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

	for (int x = 3; x < 5;x++) {
		for (int y = 2; y < 4;y++) {
			for (int z = 3; z < 5;z++) {
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

void GameController::processFrame() {
	glBegin(GL_POINTS);
	glColor3f(0, 0, 0);
	for (int x = 0; x < GRID_SIZE;x++) {
		for (int y = 0; y < GRID_SIZE;y++) {
			for (int z = 0; z < GRID_SIZE;z++) {
				glVertex3f(getGridPosition(x), getGridPosition(y), getGridPosition(z));
			}
		}
	}
	glEnd();
	for (int x = 0; x < GRID_SIZE;x++) {
		for (int y = 0; y < GRID_SIZE;y++) {
			for (int z = 0; z < GRID_SIZE;z++) {
				if (grid[x][y][z] != NULL) {
					grid[x][y][z]->process();
					grid[x][y][z]->draw();
				}
			}
		}
	}
	
}

float GameController::getGridPosition(float a) {
	return a * TILE_SIZE - GRID_OFFSET;
}