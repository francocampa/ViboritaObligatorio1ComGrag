#pragma once
#include "IGameState.h"
#include <set>
#include "GameController.h"
#include "GamePlay.h"
#include "Button.h"
#include "Level.h"

class MainMenu :
    public IGameState
{
private:
	std::vector<Button*> levelButtons;
	std::vector<Level*> levels;
	std::vector<Button*> customLevelsButtons;
	std::vector<Level*> customLevels;
	void loadLevels();
public:
	MainMenu();
	void process(float deltaTime);
	void draw();
	void startLevel(std::string levelName);
	virtual std::vector<Button*> getHudButtons();
};

