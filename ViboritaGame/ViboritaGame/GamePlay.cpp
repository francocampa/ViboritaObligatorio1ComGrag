#include "GamePlay.h"

void openSettings() {
	GameController::getInstance()->setState(new SettingsMenu(GameController::getInstance()->getSettings()));
}
void resetLevelCallback() {
	GamePlay* gp = (GamePlay*)GameController::getInstance()->getState();
	gp->resetLevel();
}
GamePlay::GamePlay(Level* level)
{
	this->level = level;
	settings = new Button("images/settings.png", "images/settingsHover.png", 580, 10, 50, 50, openSettings);
	reset = new Button("images/restart.png", "images/restartHover.png", 520, 10, 50, 50, resetLevelCallback);
	std::string sText = "0/" + std::to_string(level->getMaxScore());
	scoreText = new Button(sText.c_str(), 10, 10);
	timerText = new Button("00:00", 280, 10);
	
	startLevel();
}

void GamePlay::changeTimer(int time)
{
	int minutes = time / 60;
	int seconds = time - minutes * 60;
	std::string mString = minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes);
	std::string sString = seconds < 10 ? "0"+std::to_string(seconds) : std::to_string(seconds) ;
	std::string text = mString + ":"+ sString;
	timerText->updateText(text.c_str());
}

void GamePlay::beatLevel()
{
	std::string nextLevelName = level->getNextLevelName();
	MainMenu* mm = new MainMenu();
	GameController::getInstance()->setGamePlay(NULL);
	GameController::getInstance()->setState(mm);

	if (nextLevelName != "") {
		mm->startLevel(nextLevelName);
	}
}

void GamePlay::startLevel()
{
	std::string sText = "0/" + std::to_string(level->getMaxScore());
	scoreText->updateText(sText.c_str());
	timerText->updateText("00:00");

	this->stats = new GameStats(level->getMaxScore(), false);

	for (int x = 0; x < 8;x++) {
		for (int y = 0; y < 8;y++) {
			for (int z = 0; z < 8;z++) {
				this->grid[x][y][z] = level->getInitialGridPosition(x, y, z);
			}
		}
	}
	this->viborita = level->getInitialViborita();
	this->viborita->setGameContext(this);
	this->viborita->loadInGrid();
}

void GamePlay::resetLevel()
{
	for (int x = 0; x < 8;x++) {
		for (int y = 0; y < 8;y++) {
			for (int z = 0; z < 8;z++) {
				this->grid[x][y][z] = NULL;
			}
		}
	}
	startLevel();
}

void GamePlay::addSecond()
{
	stats->addSecond();
	changeTimer(stats->getTimer());
}

void GamePlay::process(float deltaTime)
{
	glEnable(GL_LIGHTING);
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int x = 0; x < GameController::getInstance()->GRID_SIZE;x++) {
		for (int y = 0; y < GameController::getInstance()->GRID_SIZE;y++) {
			for (int z = 0; z < GameController::getInstance()->GRID_SIZE;z++) {
				if (grid[x][y][z] != NULL && grid[x][y][z] != this->viborita) {
					grid[x][y][z]->process(deltaTime);
					grid[x][y][z]->draw();
				}
			}
		}
	}
	this->viborita->process(deltaTime);
	this->viborita->draw();
	glDisable(GL_LIGHTING);
}

void GamePlay::draw()
{
	glEnable(GL_LIGHTING);
	glNormal3f(0.0f, 1.0f, 0.0f);
	for (int x = 0; x < GameController::getInstance()->GRID_SIZE;x++) 
		for (int y = 0; y < GameController::getInstance()->GRID_SIZE;y++) 
			for (int z = 0; z < GameController::getInstance()->GRID_SIZE;z++) 
				if (grid[x][y][z] != NULL && grid[x][y][z] != this->viborita) 
					grid[x][y][z]->draw();

	this->viborita->draw();
	glDisable(GL_LIGHTING);
}

std::vector<IHudElement*> GamePlay::getHudElements()
{
	std::vector<IHudElement*> buttons;
	buttons.push_back(settings);
	buttons.push_back(reset);
	buttons.push_back(scoreText);
	buttons.push_back(timerText);
	return buttons;
}

Viborita* GamePlay::getViborita()
{
	return viborita;
}

bool GamePlay::tileHasApple(Vec3 indices)
{
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	return this->grid[x][y][z] != NULL && this->grid[x][y][z]->getType() == APPLE;
}

bool GamePlay::hasGoal(Vec3 indices)
{
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	return this->grid[x][y][z] != NULL && this->grid[x][y][z]->getType() == GOAL;
}

void GamePlay::clearTile(Vec3 indices)
{
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	this->grid[x][y][z] = NULL;
}

bool GamePlay::validTile(Vec3 indices)
{
	bool xOutside = indices.x < 0 || indices.x >= GameController::getInstance()->GRID_SIZE;
	bool yOutside = indices.y < 0 || indices.y >= GameController::getInstance()->GRID_SIZE;
	bool zOutside = indices.z < 0 || indices.z >= GameController::getInstance()->GRID_SIZE;
	return !(xOutside || yOutside || zOutside);
}

bool GamePlay::hasSolidBlock(Vec3 indices)
{
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	return grid[x][y][z] != NULL && grid[x][y][z]->getType() == BLOCK;
}

bool GamePlay::hasViborita(Vec3 indices)
{
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	return grid[x][y][z] != NULL && grid[x][y][z]->getType() == VIBORITA;
}

void GamePlay::addViborita(Vec3 indices)
{
	if (this->viborita == NULL)
		return;
	int x = indices.x;
	int y = indices.y;
	int z = indices.z;
	grid[x][y][z] = this->viborita;
}

void GamePlay::ateApple()
{
	stats->ateAnApple();
	int newScore = stats->getScore();
	int maxScore = stats->getMaxScore();

	std::string newText = std::to_string(newScore) + " / " + std::to_string(maxScore);

	scoreText->updateText(newText.c_str());
}