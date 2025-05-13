#include "GameController.h"

GameController* GameController::instance = NULL;

GameController::GameController() {
	GRID_SIZE = 8;
	TILE_SIZE = 1;
	for (int i = 0; i < 24;i++) 
		baseCubeVertices[i] = baseCubeVertices[i] * TILE_SIZE;
	for (int i = 0; i < 12;i++)
		basePyramidVertices[i] = basePyramidVertices[i] * TILE_SIZE;

	GRID_OFFSET = GRID_SIZE / 2;

	game = NULL;
	state = NULL;
	settings = NULL;
	timeCounter = 0.0f;
}

GameController* GameController::getInstance() {
	if (instance == NULL)
		instance = new GameController();

	return instance;
}

void GameController::processFrame(float deltaTime) {
	timeCounter += deltaTime;
	if (timeCounter >= 1.0) {
		timeCounter -= 1.0;
		if(game != NULL)
			game->addSecond();
	}
	
	if(settings->isWireframe())
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	state->process(deltaTime);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	HudController::getInstance()->process();
}

float GameController::getGridPosition(float a) {
	return a * TILE_SIZE - GRID_OFFSET;
}

std::vector<IHudElement*> GameController::getHudElements()
{
	return state->getHudElements();
}

void GameController::setMousePos(Vec2 mousePos)
{
	this->mousePos = mousePos;
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

void GameController::setZKey(bool z)
{
	this->z = z;
}
void GameController::setXKey(bool x)
{
	this->x = x;
}

void GameController::setSpaceKey(bool space)
{
	this->space = space;
}

void GameController::setClick(bool click)
{
	this->click = click;
}

void GameController::setMouseDown(bool click)
{
	this->mouseDown = click;
}
void GameController::setMouseUp(bool click)
{
	this->mouseUp = click;
}

void GameController::setGamePlay(GamePlay* game)
{
	this->game = game;
}

GamePlay* GameController::getGamePlay()
{
	return game;
}

Settings* GameController::getSettings()
{
	return settings;
}

void GameController::setSettings(Settings* settings)
{
	this->settings = settings;
}

IGameState* GameController::getState()
{
	return state;
}

void GameController::setState(IGameState* state)
{
	this->state = state;
}

Vec2 GameController::getMousePos()
{
	return this->mousePos;
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

bool GameController::isZKey()
{
	return z;
}

bool GameController::isXKey()
{
	return x;
}

bool GameController::isSpaceKey()
{
	return space;
}

bool GameController::clicked()
{
	return click;
}

bool GameController::isMouseDown()
{
	return mouseDown;
}

bool GameController::isMouseUp()
{
	return mouseUp;
}

Level* GameController::getLevel1()
{
	IGameEntity* grid[8][8][8];
	for (int x = 0; x < 8;x++) {
		for (int y = 0; y < 8;y++) {
			for (int z = 0; z < 8;z++) {
				grid[x][y][z] = NULL;
			}
		}
	}
	Viborita* viborita;
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
	grid[3][4][3] = new Apple(appleIndexes, applePos);
	Vec3 applePos2 = { getGridPosition(3),getGridPosition(4),getGridPosition(4) };
	Vec3 appleIndexes2 = { 3,4,4 };
	grid[3][4][4] = new Apple(appleIndexes2, applePos2);
	Vec3 applePos3 = { getGridPosition(3),getGridPosition(4),getGridPosition(5) };
	Vec3 appleIndexes3 = { 3,4,5 };
	grid[3][4][5] = new Apple(appleIndexes3, applePos3);
	Vec3 viboritaPos = { getGridPosition(5),getGridPosition(4),getGridPosition(5) };
	Vec3 viboritaIndexes = { 5,4,5 };
	viborita = new Viborita(viboritaIndexes, viboritaPos, colores);
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
	for (int x = 4; x < 7;x++) {
		for (int y = 4; y < 5;y++) {
			for (int z = 1; z < 3;z++) {
				Vec3 blockPos = { getGridPosition(x),getGridPosition(y),getGridPosition(z) };
				Vec3 blocIndexes = { x,y,z };
				grid[x][y][z] = new Block(blocIndexes, blockPos);
			}
		}
	}

	return new Level("Level 2", "Level 3", grid, 3, viborita);
}
Level* GameController::getLevel2()
{
	IGameEntity* grid[8][8][8];
	for (int x = 0; x < 8;x++) {
		for (int y = 0; y < 8;y++) {
			for (int z = 0; z < 8;z++) {
				grid[x][y][z] = NULL;
			}
		}
	}
	Viborita* viborita;
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
	grid[3][4][3] = new Apple(appleIndexes, applePos);
	Vec3 applePos2 = { getGridPosition(3),getGridPosition(4),getGridPosition(4) };
	Vec3 appleIndexes2 = { 3,4,4 };
	grid[3][4][4] = new Apple(appleIndexes2, applePos2);
	Vec3 applePos3 = { getGridPosition(3),getGridPosition(4),getGridPosition(5) };
	Vec3 appleIndexes3 = { 3,4,5 };
	grid[3][4][5] = new Apple(appleIndexes3, applePos3);
	Vec3 applePos4 = { getGridPosition(3),getGridPosition(7),getGridPosition(5) };
	Vec3 appleIndexes4 = { 3,7,5 };
	grid[3][7][5] = new Apple(appleIndexes4, applePos4);
	Vec3 viboritaPos = { getGridPosition(5),getGridPosition(4),getGridPosition(5) };
	Vec3 viboritaIndexes = { 5,4,5 };
	viborita = new Viborita(viboritaIndexes, viboritaPos, colores);

	Vec3 goalPos = { getGridPosition(2),getGridPosition(4),getGridPosition(2) };
	Vec3 goalIndexes = { 2,4,2 };
	grid[2][4][2] = new Goal(goalIndexes, goalPos);

	for (int x = 2; x < 6;x++) {
		for (int y = 2; y < 4;y++) {
			for (int z = 2; z < 6;z++) {
				Vec3 blockPos = { getGridPosition(x),getGridPosition(y),getGridPosition(z) };
				Vec3 blocIndexes = { x,y,z };
				grid[x][y][z] = new Block(blocIndexes, blockPos);
			}
		}
	}

	return new Level("Level 3","", grid, 4, viborita);
}
