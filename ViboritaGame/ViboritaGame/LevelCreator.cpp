#include "LevelCreator.h"

void selectEntityCallback(std::string entity) {
	LevelCreator* lc = (LevelCreator*)GameController::getInstance()->getState();
	if (entity == "block") {
		lc->setEntityTipe(BLOCK);
	}
	else if(entity == "apple"){
		lc->setEntityTipe(APPLE);
	}
	else if (entity == "goal") {
		lc->setEntityTipe(GOAL);
	}
	else if (entity == "viborita") {
		lc->setEntityTipe(VIBORITA);
	}
}
void selectEraseCallback(std::string z) {
	LevelCreator* lc = (LevelCreator*)GameController::getInstance()->getState();
	lc->setErase(true);
}
void goToMainMenuFromLevelCreatorCallback(std::string z) {
	LevelCreator* lc = (LevelCreator*)GameController::getInstance()->getState();
	lc->goBackToMainMenu();
}
void saveLevelCallback(std::string z) {
	LevelCreator* lc = (LevelCreator*)GameController::getInstance()->getState();
	lc->saveLevel();
}
void changeNameCallback(std::string name) {
	LevelCreator* lc = (LevelCreator*)GameController::getInstance()->getState();
	lc->setName(name);
}
int LevelCreator::autoId = 0;
LevelCreator::LevelCreator()
{
	int maxId = 0;
	noOfApples = 0;
	for (const auto& entry : std::filesystem::directory_iterator("customLevels")) 
		if (entry.is_regular_file()) {
			std::string fileName = entry.path().filename().string();
			int newId = 0;
			try {
				newId = std::stoi(fileName.substr(0, fileName.size() - 3));
			}catch(std::invalid_argument){}
			if (newId > maxId) {
				maxId = newId;
			}
		}

	autoId= maxId+1;

	createButtons();
	selectedGridIndex = { 0,0,0 };
	selectedEntityType = BLOCK;
	this->viborita = NULL;
	for (int x = 0; x < 8;x++)
		for (int y = 0; y < 8;y++)
			for (int z = 0; z < 8;z++)
				grid[x][y][z] = NULL;
}
void LevelCreator::createButtons()
{
	blockButton = new Button("Bloque", 10, 10, selectEntityCallback, "block");
	appleButton = new Button("Manzana", 10, 52, selectEntityCallback, "apple");
	goalButton = new Button("Meta", 10, 94, selectEntityCallback, "goal");
	viboritaButton = new Button("Viborita", 10, 136, selectEntityCallback, "viborita");
	erasorButton = new Button("Borrador", 10, 178, selectEraseCallback, "");
	
	nameField = new TextField("Nombre", 10, 300, 200, changeNameCallback, "");
	saveButton = new Button("Guardar", 10, 350, saveLevelCallback, "");
	mainMenuButton = new Button("Volver al menu", 10, 392, goToMainMenuFromLevelCreatorCallback, "");
	//erasorButton = new Button("Borrador",10,178,100,32,selectEraseCallback,"");
}
void LevelCreator::process(float deltaTime)
{
	GameController* gc = GameController::getInstance();
	handleSelectedIndexMovement();
	handlePlaceEntity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	GLfloat bigCube[24];
	for (int i = 0;i < 24;i++) {
		bigCube[i] = baseCubeVertices[i] * gc->TILE_SIZE * gc->GRID_SIZE;
	}
	float offset = -gc->GRID_SIZE*gc->TILE_SIZE/2;
	glTranslatef(offset,offset,offset);
	drawCube(bigCube, baseCubeColors, baseCubeIndices);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(gc->getGridPosition(selectedGridIndex.x), gc->getGridPosition(selectedGridIndex.y), gc->getGridPosition(selectedGridIndex.z));
	drawCube(baseCubeVertices, baseCubeColors, baseCubeIndices);
	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_LIGHTING);
	for (int x = 0; x < gc->GRID_SIZE;x++) 
		for (int y = 0; y < gc->GRID_SIZE;y++) 
			for (int z = 0; z < gc->GRID_SIZE;z++) 
				if (grid[x][y][z] != NULL && grid[x][y][z] != this->viborita) 
					grid[x][y][z]->draw();
				
	if(this->viborita != NULL)
		this->viborita->draw();	
	glDisable(GL_LIGHTING);
}

void LevelCreator::draw()
{
}

std::vector<IHudElement*> LevelCreator::getHudElements()
{
	std::vector<IHudElement*> btns;
	btns.push_back(blockButton);
	btns.push_back(appleButton);
	btns.push_back(goalButton);
	btns.push_back(viboritaButton);
	btns.push_back(erasorButton);
	btns.push_back(saveButton);
	btns.push_back(mainMenuButton);
	btns.push_back(nameField);
	return btns;
}

void LevelCreator::setEntityTipe(GAME_ENTITY_TYPE type)
{
	this->selectedEntityType = type;
	this->erase = false;
}

void LevelCreator::setErase(bool erase)
{
	this->erase = erase;
}

std::string entityTypeString(GAME_ENTITY_TYPE type) {
	switch (type) {
	case BLOCK:
		return "block";
	case VIBORITA:
		return "viborita";
	case APPLE:
		return "apple";
	case GOAL:
		return "goal";
	default:
		return "";
	}
}
void LevelCreator::saveLevel()
{
	if (this->viborita == NULL)
		return;
	GameController* gc = GameController::getInstance();

	pugi::xml_document* root = new pugi::xml_document();
	pugi::xml_node levelNode = root->append_child("Level");
	levelNode.append_attribute("name").set_value(autoId);
	levelNode.append_attribute("maxScore").set_value(noOfApples);
	levelNode.append_attribute("nextLevel").set_value(autoId+1);
	
	

	pugi::xml_node gridNode = levelNode.append_child("Grid");
	for (int x = 0; x < gc->GRID_SIZE;x++)
		for (int y = 0; y < gc->GRID_SIZE;y++)
			for (int z = 0; z < gc->GRID_SIZE;z++) {
				if (grid[x][y][z] != NULL && grid[x][y][z] != this->viborita) {
					pugi::xml_node entityNode = gridNode.append_child("GameEntity");
					entityNode.append_attribute("type").set_value(entityTypeString(grid[x][y][z]->getType()));
					entityNode.append_attribute("x").set_value(x);
					entityNode.append_attribute("y").set_value(y);
					entityNode.append_attribute("z").set_value(z);
				}
			}

	pugi::xml_node viboritaNode = levelNode.append_child("Viborita");
	ViboritaPart* aux = this->viborita->getHead();
	while (aux != NULL) {
		pugi::xml_node bodyPartNode =  viboritaNode.append_child("BodyPart");
		bodyPartNode.append_attribute("x").set_value(aux->gridIndex.x);
		bodyPartNode.append_attribute("y").set_value(aux->gridIndex.y);
		bodyPartNode.append_attribute("z").set_value(aux->gridIndex.z);
		aux = aux->next;
	}

	std::string filePath = "customLevels/" + std::to_string(autoId) + ".xml";
	
	root->save_file(filePath.c_str());

	autoId++;
}

void LevelCreator::clearGrid()
{
}

void LevelCreator::goBackToMainMenu()
{
	MainMenu* mm = new MainMenu();
	GameController::getInstance()->setState(mm);
}

void LevelCreator::setName(std::string name)
{
	this->name = name;
}

void LevelCreator::handleSelectedIndexMovement()
{
	GameController* gc = GameController::getInstance();
	if (gc->isArrowUp() && selectedGridIndex.z + 1 < gc->GRID_SIZE)
		selectedGridIndex.z += 1;
	else if (gc->isArrowDown() && selectedGridIndex.z - 1 >= 0)
		selectedGridIndex.z += -1;
	else if (gc->isArrowLeft() && selectedGridIndex.x + 1 < gc->GRID_SIZE)
		selectedGridIndex.x += 1;
	else if (gc->isArrowRight() && selectedGridIndex.x - 1 >= 0)
		selectedGridIndex.x += -1;
	else if (gc->isZKey() && selectedGridIndex.y + 1 < gc->GRID_SIZE)
		selectedGridIndex.y += 1;
	else if (gc->isXKey() && selectedGridIndex.y - 1 >= 0)
		selectedGridIndex.y += -1;
}

void LevelCreator::handlePlaceEntity()
{
	GameController* gc = GameController::getInstance();
	if (!gc->isSpaceKey())
		return;

	int x = selectedGridIndex.x;
	int y = selectedGridIndex.y;
	int z = selectedGridIndex.z;
	/*if (grid[x][y][z] != NULL) {
		delete grid[x][y][z];
	}*/
	if (this->erase && grid[x][y][z] != NULL) {
		IGameEntity* toDelete = grid[x][y][z];
		grid[x][y][z] = NULL;
		if(toDelete->getType() == APPLE)
			noOfApples--;
		else if(toDelete->getType() == VIBORITA) {
			this->viborita->removeBodyFromGridIndex(x,y,z);
			if (this->viborita->getSize() == 0)
			{
				this->viborita = NULL;
				//TODO: agregar el delete
			}

			return;
		}
		//TODO: ver por qu[e crashea con el delete toDelete;
		return;
	}
	Vec3 gridIndex = { x,y,z };
	Vec3 position = {gc->getGridPosition(x),gc->getGridPosition(y) ,gc->getGridPosition(z) };
	switch (selectedEntityType)
	{
	case BLOCK:
		grid[x][y][z] = new Block(gridIndex,position);
		break;
	case VIBORITA:
		if (this->viborita == NULL) {
			this->viborita = new Viborita(gridIndex,position,baseViboritaColors);
		}
		else {
			this->viborita->addTail(gridIndex);
		}
		grid[x][y][z] = this->viborita;
		break;
	case APPLE:
		grid[x][y][z] = new Apple(gridIndex, position);
		noOfApples++;
		break;
	case GOAL:
		grid[x][y][z] = new Goal(gridIndex, position);
		break;
	default:
		break;
	}
}
