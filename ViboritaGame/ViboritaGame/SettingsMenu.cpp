#include "SettingsMenu.h"

void goBackToGameCallback(std::string s) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();

	sm->goBackToGame();
}
void setSpeedCallback(float speed) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->changeGameSpeed(speed);
}
void setLightAngleCallback(float angle) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->changeLightAngle(angle);
}
void setWireframeCallback(std::string wireframe) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->setWireframe(wireframe == "true");
}
void setTexturesCallback(std::string textures) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->setTextures(textures == "true");
}
void setTexSettingsCallback(std::string setting) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	if(setting == "interpolado")
		sm->setTexSettings(INTERPOLADO);
	else
		sm->setTexSettings(FACETADO);
}
void goToMainMenuFromSettingsCallback(std::string z) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->goBackToMainMenu();
}
SettingsMenu::SettingsMenu(Settings* settings) {
	this->settings = settings;

	speedText = new Button("Velocidad",220,20,100,32);
	speedSlider = new Slider("Prueba", 220, 70, 150, 0.5f, 3.0f, setSpeedCallback, 1.0f);

	wireFrameText = new Button("Wireframe", 220, 120, 100, 32);
	wireFrameTrue = new Button("images/Checkbox.png", "images/CheckboxHover.png", "images/CheckboxSelected.png", 240, 160, 40, 40, setWireframeCallback, "true");
	wireFrameFalse = new Button("images/Checkbox.png", "images/CheckboxHover.png", "images/CheckboxSelected.png", 290, 160, 40, 40, setWireframeCallback, "false");
	if (settings->isWireframe())
	{
		wireFrameTrue->setSelected(true);
		wireFrameFalse->setSelected(false);
	}
	else {
		wireFrameTrue->setSelected(false);
		wireFrameFalse->setSelected(true);
	}
	texturesText = new Button("Textures", 220, 220, 100, 32);
	texturesTrue = new Button("images/Checkbox.png", "images/CheckboxHover.png", "images/CheckboxSelected.png", 240, 260, 40, 40, setTexturesCallback, "true");
	texturesFalse = new Button("images/Checkbox.png", "images/CheckboxHover.png", "images/CheckboxSelected.png", 290, 260, 40, 40, setTexturesCallback, "false");
	if (settings->hasTextures())
	{
		texturesTrue->setSelected(true);
		texturesFalse->setSelected(false);
	}
	else {
		texturesTrue->setSelected(false);
		texturesFalse->setSelected(true);
	}

	interpoladoText = new Button("Interpolado", 220, 320, 100, 32);
	interpoladoCheck = new Button("images/Checkbox.png", "images/CheckboxHover.png", "images/CheckboxSelected.png", 240, 360, 40, 40, setTexSettingsCallback, "interpolado");
	facetadoText = new Button("Facetado", 330, 320, 100, 32);
	facetadoCheck = new Button("images/Checkbox.png", "images/CheckboxHover.png", "images/CheckboxSelected.png", 350, 360, 40, 40, setTexSettingsCallback, "facetado");
	if (settings->getTexSettings() == INTERPOLADO)
	{
		interpoladoCheck->setSelected(true);
		facetadoCheck->setSelected(false);
	}
	else {
		interpoladoCheck->setSelected(false);
		facetadoCheck->setSelected(true);
	}

	lightDirText = new Button("Direccion de luz", 220, 420, 100, 32);
	lightDirSlider = new Slider("Prueba", 220, 460, 150, 0, 360, setLightAngleCallback, settings->getLightAngle());

	backToMenu = new Button("Volver al menu", 340, 10, 200, 32, goToMainMenuFromSettingsCallback, "");
	backToGame = new Button("X", 580, 10, 50, 50, goBackToGameCallback,"");
}

void SettingsMenu::changeGameSpeed(float speed)
{
	this->settings->setGameSpeed(speed);
}

void SettingsMenu::setWireframe(bool wireframe)
{
	if (wireframe)
	{
		wireFrameTrue->setSelected(true);
		wireFrameFalse->setSelected(false);
	}else{
		wireFrameTrue->setSelected(false);
		wireFrameFalse->setSelected(true);
	}
	this->settings->setWireframe(wireframe);
}

void SettingsMenu::setTextures(bool texture)
{
	if (texture)
	{
		texturesTrue->setSelected(true);
		texturesFalse->setSelected(false);
	}
	else {
		texturesTrue->setSelected(false);
		texturesFalse->setSelected(true);
	}
	this->settings->setTextures(texture);
}

void SettingsMenu::setTexSettings(TEX_SETTINGS texSettings)
{
	if (texSettings == INTERPOLADO)
	{
		interpoladoCheck->setSelected(true);
		facetadoCheck->setSelected(false);
	}
	else {
		interpoladoCheck->setSelected(false);
		facetadoCheck->setSelected(true);
	}
	this->settings->setTexSettings(texSettings);
}

void SettingsMenu::changeLightAngle(int angle)
{
	this->settings->setLightAngle(angle);
}

void SettingsMenu::goBackToGame()
{
	GameController::getInstance()->setState(GameController::getInstance()->getGamePlay());
}

void SettingsMenu::goBackToMainMenu()
{
	MainMenu* mm = new MainMenu();
	GameController::getInstance()->setState(mm);
}

void SettingsMenu::process(float deltaTime)
{
}

void SettingsMenu::draw()
{
}

std::vector<IHudElement*> SettingsMenu::getHudElements()
{
	std::vector<IHudElement*> buttons;
	buttons.push_back(speedText);
	buttons.push_back(speedSlider);
	buttons.push_back(wireFrameText);
	buttons.push_back(wireFrameTrue);
	buttons.push_back(wireFrameFalse);
	buttons.push_back(texturesText);
	buttons.push_back(texturesTrue);
	buttons.push_back(texturesFalse);
	buttons.push_back(backToGame);
	buttons.push_back(interpoladoText);
	buttons.push_back(interpoladoCheck);
	buttons.push_back(facetadoText);
	buttons.push_back(facetadoCheck);
	buttons.push_back(backToMenu);
	buttons.push_back(lightDirText);
	buttons.push_back(lightDirSlider);
	return buttons;
}