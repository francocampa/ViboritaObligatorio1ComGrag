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

	//colores de la viborita
	GLfloat colores[] = {
		0.20, 0.20, 0.20,
		0.30, 0.30, 0.30,
		0.50, 0.50, 0.50,
		0.70, 0.70, 0.70,
		0.90, 0.90, 0.90,
		0.110, 0.110, 0.110
	};
	Vec3 applePos = { getGridPosition(3),getGridPosition(4),getGridPosition(3) };
	Vec3 appleIndexes = { 3,4,3 };
	grid[3][4][3] = new Apple(appleIndexes,applePos);
	Vec3 applePos2 = { getGridPosition(3),getGridPosition(4),getGridPosition(4) };
	Vec3 appleIndexes2 = { 3,4,4 };
	grid[3][4][4] = new Apple(appleIndexes2, applePos2);
	Vec3 applePos3 = { getGridPosition(3),getGridPosition(4),getGridPosition(5) };
	Vec3 appleIndexes3 = { 3,4,5 };
	grid[3][4][5] = new Apple(appleIndexes3, applePos3);
	Vec3 viboritaPos = { getGridPosition(5),getGridPosition(4),getGridPosition(5) };
	Vec3 viboritaIndexes = { 5,4,5 };
	this->viborita = new Viborita(viboritaIndexes, viboritaPos, colores); 
	grid[5][4][5] = this->viborita;//posición donde empieza la viborita
	Vec3 goalPos = { getGridPosition(2),getGridPosition(4),getGridPosition(2) };
	Vec3 goalIndexes = { 2,4,2 };
	grid[2][4][2] = new Goal(goalIndexes, goalPos);

	for (int x = 0; x < 6;x++) {
		for (int y = 2; y < 4;y++) {
			for (int z = 0; z < 6;z++) {
				Vec3 blockPos = { getGridPosition(x),getGridPosition(y),getGridPosition(z) };
				Vec3 blocIndexes = { x,y,z };
				grid[x][y][z] = new Block(blocIndexes, blockPos);
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
				if (grid[x][y][z] != NULL && grid[x][y][z] != this->viborita) {
					grid[x][y][z]->process(deltaTime);
					grid[x][y][z]->draw();
				}
			}
		}
	}
	this->viborita->process(deltaTime);
	this->viborita->draw();
}

float GameController::getGridPosition(float a) {
	return a * TILE_SIZE - GRID_OFFSET;
}

Viborita* GameController::getViborita() {
	return this->viborita;
}

bool GameController::tileHasApple(Vec3 indices)
{
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	return this->grid[x][y][z] != NULL && this->grid[x][y][z]->getType() == APPLE; //Ta mal, habr[ia que agregar en gameEntity un getType para que te retorne si es unbloque o si es una manzana o la meta o yqs
}

void GameController::clearTile(Vec3 indices)
{
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	this->grid[x][y][z] = NULL;
}

bool GameController::validTile(Vec3 indices)
{
	bool xOutside = indices.x < 0 || indices.x >= GRID_SIZE;
	bool yOutside = indices.y < 0 || indices.y >= GRID_SIZE;
	bool zOutside = indices.z < 0 || indices.z >= GRID_SIZE;
	return !(xOutside || yOutside || zOutside);
}

bool GameController::hasSolidBlock(Vec3 indices)
{
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	return grid[x][y][z]!= NULL && grid[x][y][z]->getType() == BLOCK;
}

bool GameController::hasViborita(Vec3 indices)
{
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	return grid[x][y][z] != NULL && grid[x][y][z]->getType() == VIBORITA;
}

void GameController::addViborita(Vec3 indices)
{
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	grid[x][y][z] = this->viborita;
}

void GameController::setArrowUp(bool up)
{
	this->up = up;
}

void GameController::setArrowDown(bool down)
{
	this->down = down;
}

void GameController::setArrowLeft(bool left)
{
	this->left = left;
}

void GameController::setArrowRight(bool right)
{
	this->right = right;
}

bool GameController::isArrowUp()
{
	return up;
}
bool GameController::isArrowDown()
{
	return down;
}
bool GameController::isArrowLeft()
{
	return left;
}
bool GameController::isArrowRight()
{
	return right;
}
