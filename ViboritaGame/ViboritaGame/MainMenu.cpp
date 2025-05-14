#include "MainMenu.h"

void loadLevel(std::string levelName) {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();

	mm->startLevel(levelName);
}
void goToLevelCreatorFromMainMenuCallback(std::string z) {
	MainMenu* mm = (MainMenu*)GameController::getInstance()->getState();
	mm->goToLevelCreator();
}

void callbackForSlider(float newValue) {
	printf("%f\n",newValue);
}

MainMenu::MainMenu() {
	levelCreatorButton = new Button("Creador de niveles", 10, 10, goToLevelCreatorFromMainMenuCallback, "");

	loadLevels();

	std::vector<Button*> btns;
	int i = 0;
	int j = 0;
	int prevWidth = 0;
	for (Level* level : levels) {
		Button* levelBtn = new Button(level->getName().c_str(), 50 + 20*i + prevWidth , 120 + j * 60, loadLevel, level->getName());
		btns.push_back(levelBtn);
		i++;
		if (i == 5) {
			i = 0;
			j++;
		}
		prevWidth += levelBtn->getRect()->w;
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

void MainMenu::goToLevelCreator()
{
	LevelCreator* lc = new LevelCreator();
	GameController::getInstance()->setState(lc);
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
		loadFromXML(levelXMLReader.child("Level"));
	}
	for (std::string levelFile : customLevelsFiles) {
		std::string fullPath = "customLevels/" + levelFile;
		pugi::xml_parse_result result = levelXMLReader.load_file(fullPath.c_str());
		loadFromXML(levelXMLReader.child("Level"));
	}

	//levels.push_back(GameController::getInstance()->getLevel1());
	//levels.push_back(GameController::getInstance()->getLevel2());
}

void MainMenu::loadFromXML(pugi::xml_node levelNode)
{
	if (!levelNode) {
		printf("Error loading level: %s. A Level node is required as root of the XML file");
		return;
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
		return;
	}
	if (!gridNode) {
		printf("Error loading level: %s. A Grid node is required inside the main Level node");
		return;
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
	levels.push_back(level);
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
	buttons.push_back(levelCreatorButton);
	for (Button* button : this->levelButtons)
		buttons.push_back(button);
	return buttons;
}
