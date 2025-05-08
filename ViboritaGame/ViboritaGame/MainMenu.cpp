#include "MainMenu.h"

void loadLevel(std::string levelName) {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();

	mm->startLevel(levelName);
}

MainMenu::MainMenu() {
	std::vector<Level*> levels;
	levels.push_back(GameController::getInstance()->getLevel1());
	levels.push_back(GameController::getInstance()->getLevel2());

	this->levels = levels;

	std::vector<Button*> btns;
	int i = 0;
	int j = 0;
	for (Level* level : levels) {
		Button* levelBtn = new Button(level->getName().c_str(), 50+i*60, 120+j*60, 50, 50,loadLevel,level->getName());
		btns.push_back(levelBtn);
		i++;
		if (i == 5) {
			i = 0;
			j++;
		}
	}
	this->levelButtons = btns;
}


void MainMenu::startLevel(std::string levelName)
{
	for (Level* level : levels) {
		if (level->getName() == levelName) {
			GamePlay* gp = new GamePlay(level);
			GameController::getInstance()->setState(gp);
			GameController::getInstance()->setGamePlay(gp);
			return;
		}
	}
	for (Level* level : customLevels) {
		if (level->getName() == levelName) {
			GamePlay* gp = new GamePlay(level);
			GameController::getInstance()->setState(gp);
			GameController::getInstance()->setGamePlay(gp);
			return;
		}
	}

	//yqs error de que no encontr[o el nivel :D

}

void MainMenu::loadLevels()
{
}

void MainMenu::process(float deltaTime)
{
}

void MainMenu::draw()
{
}

std::vector<Button*> MainMenu::getHudButtons()
{
	std::vector<Button*> buttons;
	for (Button* button : this->levelButtons)
		buttons.push_back(button);
	return buttons;
}
