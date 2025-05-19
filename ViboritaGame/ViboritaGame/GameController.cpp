#include "GameController.h"

GameController* GameController::instance = NULL;

std::mt19937 generador(std::time(nullptr));
std::uniform_int_distribution<> angles(1, 100);
std::uniform_int_distribution<> radios(3, 11);
std::uniform_int_distribution<> cloudModel(1, 3);

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
	fps = 0;
	fpsBtn = new Button("60", 10, 400);

	for (int i = 0; i < 4; i++) {
		clouds[i] = new Cloud(cloudModel(generador), radios(generador), cloudModel(generador));
	}
}

GameController* GameController::getInstance() {
	if (instance == NULL)
		instance = new GameController();

	return instance;
}

void GameController::processFrame(float deltaTime) {
	fps++;
	timeCounter += deltaTime;
	if (timeCounter >= 1.0) {
		timeCounter -= 1.0;
		fpsBtn->updateText(std::to_string(fps).c_str());
		fps = 1;
		if (game != NULL)
			game->addSecond();
	}

	if (settings->isWireframe())
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (game != NULL) {
		for (int i = 0; i < 4; i++) {
			glEnable(GL_LIGHTING);
			if (!paused) {
				clouds[i]->process(deltaTime);
			}
			clouds[i]->draw();
			glDisable(GL_LIGHTING);
		}
	}

	state->process(deltaTime);

	std::list<ParticleSystem*>::iterator it;
	it = particles.begin();
	while (!particles.empty() && it != particles.end()) {
		ParticleSystem* ps = (*it);
		paused ? ps->draw() : ps->process(deltaTime);
		if (ps->shouldDissapear()) {
			delete ps;
			it = particles.erase(it);
		}else
			it++;
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	HudController::getInstance()->process(deltaTime);
}

float GameController::getGridPosition(float a) {
	return a * TILE_SIZE - GRID_OFFSET;
}

std::vector<IHudElement*> GameController::getHudElements()
{
	std::vector<IHudElement*> elements = state->getHudElements();
	if (showFps)
		elements.push_back(fpsBtn);
	return elements;
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

void GameController::setShowFps(bool show)
{
	this->showFps = show;
}

void GameController::setKeyPressed(std::string key)
{
	this->keyPressed = key;
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

bool GameController::isShowFps()
{
	return showFps;
}

std::string GameController::getKeyPressed()
{
	return keyPressed;
}

void GameController::setMoveCamera(bool move)
{
	this->moveCamera = move;
}

bool GameController::getMoveCamera()
{
	return moveCamera;
}

Vec3 GameController::getCameraProps()
{
	return cameraProps;
}

float GameController::getSensitivity()
{
	return sensitivity;
}

bool GameController::isPaused()
{
	return paused;
}

void GameController::setPaused(bool paused)
{
	this->paused = paused;
}

void GameController::setCameraCoordinates(float theta, float phi)
{
	cameraProps.x = theta;
	cameraProps.y = phi;
}

void GameController::setCameraRadius(float radius)
{
	cameraProps.z = radius;
}

void GameController::setSensitivity(float sensitivity)
{
	this->sensitivity = sensitivity;
}

void GameController::setCameraPos(Vec3 pos)
{
	cameraPos.x = pos.x;
	cameraPos.y = pos.y;
	cameraPos.z = pos.z;
}

Vec3 GameController::getCameraPos()
{
	return cameraPos;
}

void GameController::close()
{
	this->closeFlag = true;
}

bool GameController::shouldClose()
{
	return closeFlag;
}

void GameController::addParticles(ParticleSystem* ps)
{
	if (particles.size() < 20)
		particles.push_back(ps);
	else
		delete ps;
}

void GameController::removeParticles(ParticleSystem* ps)
{
	std::list<ParticleSystem*>::iterator it;
	it = particles.begin();
	while (!particles.empty() && it != particles.end()) {
		ParticleSystem* toDel = (*it);
		if(toDel != toDel)
		{
			it++;
			continue;
		}
		delete ps;
		particles.erase(it);
		break;
	}
}





