#pragma once
#include "IGameState.h"
#include <set>
#include "GameController.h"
#include "GamePlay.h"
#include "Button.h"
#include "Level.h"
#include "pugixml.hpp"
#include <iostream>
#include <filesystem>
#include "LevelCreator.h"

class MainMenu :
    public IGameState
{
private:
	Button* levelCreatorButton;
	std::vector<Button*> levelButtons;
	std::vector<Level*> levels;
	std::vector<Button*> customLevelsButtons;
	std::vector<Level*> customLevels;
	void loadLevels();
	Level* loadFromXML(pugi::xml_node root);
public:
	MainMenu();
	void process(float deltaTime);
	void draw();
	void startLevel(std::string levelName);
	void goToLevelCreator();
	virtual std::vector<IHudElement*> getHudElements();
};

