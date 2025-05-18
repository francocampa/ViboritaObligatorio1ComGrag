#include "MainMenu.h"
#include "LevelButton.h"

void goToLevelCreatorFromMainMenuCallback(std::string z) {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();
	mm->goToLevelCreator();
}


void goToSettingsFromMainMenuCallback(std::string z) {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();
	mm->goToSettings();
}

void closeFromMenuCallback(std::string z) {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();
	mm->closeGame();
}

void callbackForSlider(float newValue) {
	printf("%f\n",newValue);
}

void callbackShowLevelCarousel(std::string z) {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();
	mm->setLevelCarousel();
}
void callbackShowCustomLevelCarousel(std::string z) {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();
	mm->setCustomLevelCarousel();
}

void callbackCarouselRight() {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();
	mm->moveCarouselRight();
}
void callbackCarouselLeft() {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();
	mm->moveCarouselLeft();
}
void callbackCloseCarousel(std::string z) {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();
	mm->closeCarousel();
}
void loadLevel(std::string levelName) {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();

	mm->startLevel(levelName);
}

MainMenu::MainMenu() {
	
	showLevelCarousel = new Button("Niveles", 0, 150, callbackShowLevelCarousel, "", false,false);
	showLevelCarousel->center(0, 640);
	
	showCustomLevelCarousel = new Button("Niveles personalizados", 0, 200, callbackShowCustomLevelCarousel, "", false,false);
	showCustomLevelCarousel->center(0, 640);
	
	levelCreatorButton = new Button("Creador de niveles", 0, 250, goToLevelCreatorFromMainMenuCallback, "", false, false);
	levelCreatorButton->center(0, 640);

	settingsButton = new Button("Opciones", 0, 300, goToSettingsFromMainMenuCallback, "", false, false);
	settingsButton->center(0, 640);

	closeButton = new Button("Salir", 0, 400, closeFromMenuCallback, "", false, false);
	closeButton->center(0, 640);


	leftArrowCarousel = new Button("images/carousel-left.png", "images/carousel-left-hover.png",10,480/2 - 30/2, 30,30,callbackCarouselLeft);
	rightArrowCarousel = new Button("images/carousel-right.png", "images/carousel-right-hover.png", 640 - 10 - 30 / 2, 480 / 2 - 30 / 2, 30, 30, callbackCarouselRight);
	closeCarouselBtn = new Button("X", 640 - 10 - 30 / 2, 10, callbackCloseCarousel, "", false, false);

	loadLevels();

	std::vector<LevelButton*> btns;
	int i = 0;
	for (Level* level : levels) {
		LevelButton* levelBtn = new LevelButton(i%3,level,loadLevel);
		btns.push_back(levelBtn);
		i++;
	}
	this->levelButtons = btns;
	
	std::vector<LevelButton*> btnsForCustom;
	i = 0;
	for (Level* level : customLevels) {
		LevelButton* levelBtn = new LevelButton(i%3, level, loadLevel);
		btnsForCustom.push_back(levelBtn);
		i++;
	}
	this->customLevelsButtons = btnsForCustom;

	this->showCarousel = false;
	this->levelCarousel = btnsForCustom;
	this->carouselIndex = 0;
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

void MainMenu::goToLevelCreator()
{
	LevelCreator* lc = new LevelCreator();
	GameController::getInstance()->setState(lc);
}

void MainMenu::goToSettings()
{
	SettingsMenu* s = new SettingsMenu(GameController::getInstance()->getSettings());
	GameController::getInstance()->setState(s);
}

void MainMenu::closeGame()
{
	GameController::getInstance()->close();
}

void MainMenu::moveCarouselRight()
{
	if (levelCarousel.size() < (carouselIndex+1) * 3)
		return;

	carouselIndex++;
}

void MainMenu::moveCarouselLeft()
{
	if (carouselIndex == 0)
		return;

	carouselIndex--;
}

void parseCoordsFromXMLNode(pugi::xml_node node, Vec3 &gridIndex, Vec3 &position) {
	float x = std::stoi(node.attribute("x").value());
	float y = std::stoi(node.attribute("y").value());
	float z = std::stoi(node.attribute("z").value());
	gridIndex = { x,y,z };
	position = { GameController::getInstance()->getGridPosition(x),GameController::getInstance()->getGridPosition(y),GameController::getInstance()->getGridPosition(z) };
}

void MainMenu::loadLevels()
{
	std::vector<std::string> levelFiles;
	std::vector<std::string> customLevelsFiles;

	for (const auto& entry : std::filesystem::directory_iterator("levels")) {
		if (entry.is_regular_file()) { 
			levelFiles.push_back(entry.path().filename().string());
		}
	}
	for (const auto& entry : std::filesystem::directory_iterator("customLevels")) {
		if (entry.is_regular_file()) {
			customLevelsFiles.push_back(entry.path().filename().string());
		}
	}

	pugi::xml_document levelXMLReader;
	for (std::string levelFile:levelFiles) {
		std::string fullPath = "levels/" + levelFile;
		pugi::xml_parse_result result = levelXMLReader.load_file(fullPath.c_str());
		Level * l = loadFromXML(levelXMLReader.child("Level"));
		levels.push_back(l);
	}
	for (std::string levelFile : customLevelsFiles) {
		std::string fullPath = "customLevels/" + levelFile;
		pugi::xml_parse_result result = levelXMLReader.load_file(fullPath.c_str());
		Level* l =loadFromXML(levelXMLReader.child("Level"));
		customLevels.push_back(l);
	}
}

Level* MainMenu::loadFromXML(pugi::xml_node levelNode)
{
	if (!levelNode) {
		printf("Error loading level: %s. A Level node is required as root of the XML file");
		return NULL;
	}
	std::string levelName = levelNode.attribute("name").value();
	int maxScore = std::stoi(levelNode.attribute("maxScore").value());
	std::string nextLevel = "";
	if (levelNode.attribute("nextLevel"))
		std::string nextLevel = levelNode.attribute("nextLevel").value();

	pugi::xml_node viboritaNode = levelNode.child("Viborita");
	pugi::xml_node gridNode = levelNode.child("Grid");

	if (!viboritaNode) {
		printf("Error loading level: %s. A Vivorita node is required inside the main Level node");
		return NULL;
	}
	if (!gridNode) {
		printf("Error loading level: %s. A Grid node is required inside the main Level node");
		return NULL;
	}

	IGameEntity* grid[8][8][8];
	for (int x = 0; x < 8;x++)
		for (int y = 0; y < 8;y++)
			for (int z = 0; z < 8;z++)
				grid[x][y][z] = NULL;

	for (pugi::xml_node gameEntity = gridNode.child("GameEntity"); gameEntity; gameEntity = gameEntity.next_sibling("GameEntity")) {
		IGameEntity* gi = NULL;
		std::string type = gameEntity.attribute("type").value();

		Vec3 gridIndex = { 0,0,0 };
		Vec3 position = { 0,0,0 };
		parseCoordsFromXMLNode(gameEntity, gridIndex, position);
		if (type == "block") {
			gi = new Block(gridIndex, position);
		}
		else if (type == "apple") {
			gi = new Apple(gridIndex, position);
		}
		else if (type == "goal") {
			gi = new Goal(gridIndex, position);
		}
		grid[(int)gridIndex.x][(int)gridIndex.y][(int)gridIndex.z] = gi;
	}

	pugi::xml_node viboritaHeadNode = viboritaNode.child("BodyPart");
	Vec3 gridIndex = { 0,0,0 };
	Vec3 position = { 0,0,0 };
	parseCoordsFromXMLNode(viboritaHeadNode, gridIndex, position);

	Viborita* viborita = new Viborita(gridIndex, position, baseViboritaColors);
	Vec3 voidVec = { 0,0,0 };
	for (pugi::xml_node viboritaBodyPartNode = viboritaHeadNode.next_sibling(); viboritaBodyPartNode; viboritaBodyPartNode = viboritaBodyPartNode.next_sibling("BodyPart")) {
		Vec3 partGridIndex = { 0,0,0 };
		parseCoordsFromXMLNode(viboritaBodyPartNode, partGridIndex, voidVec);
		viborita->addTail(partGridIndex);
	}

	Level* level = new Level(levelName, nextLevel, grid, maxScore, viborita);
	
	return level;
}

void MainMenu::process(float deltaTime)
{
}

void MainMenu::draw()
{
}

std::vector<IHudElement*> MainMenu::getHudElements()
{
	std::vector<IHudElement*> buttons;
	if (showCarousel) {
		buttons.push_back(levelCarousel.at(carouselIndex * 3));
		if (levelCarousel.size() > carouselIndex * 3 + 1)
			buttons.push_back(levelCarousel.at(carouselIndex * 3 + 1));
		if (levelCarousel.size() > carouselIndex * 3 + 2)
			buttons.push_back(levelCarousel.at(carouselIndex * 3 + 2));

		buttons.push_back(leftArrowCarousel);
		buttons.push_back(rightArrowCarousel);
		buttons.push_back(closeCarouselBtn);
	}
	else {
		buttons.push_back(showLevelCarousel);
		buttons.push_back(showCustomLevelCarousel);
		buttons.push_back(levelCreatorButton);
		buttons.push_back(closeButton);
		buttons.push_back(settingsButton);
	}

	
	return buttons;
}

void MainMenu::setLevelCarousel()
{
	this->showCarousel = true;
	this->carouselIndex = 0;
	this->levelCarousel = this->levelButtons;
}

void MainMenu::setCustomLevelCarousel()
{
	this->showCarousel = true;
	this->carouselIndex = 0;
	this->levelCarousel = this->customLevelsButtons;
}

void MainMenu::closeCarousel()
{
	this->showCarousel = false;
}
