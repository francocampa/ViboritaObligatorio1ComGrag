#include "SettingsMenu.h"

void goBackToGameCallback(std::string s) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();

	sm->goBackToGame();
}
void setSpeedCallback(float speed) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->changeGameSpeed(speed);
}
void setVolumeCallback(float volume) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->changeVolume(volume);
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
void setFacetadoCallback(std::string textures) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->setFacetado(textures == "true");
}
void setInterpoladoCallback(std::string textures) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->setInterpolado(textures == "true");
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
void setLightRedCallback(float red) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->changeLightRed(red);
}
void setLightGreenCallback(float green) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->changeLightGreen(green);
}
void setLightBlueCallback(float blue) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->changeLightBlue(blue);
}
void setLightAlphaCallback(float alpha) {
	SettingsMenu* sm = (SettingsMenu*)GameController::getInstance()->getState();
	sm->changeLightAlpha(alpha);
}
SettingsMenu::SettingsMenu(Settings* settings) {
	this->settings = settings;

	speedText = new Button("Velocidad",20,20);
	speedSlider = new Slider("Prueba", 30, 70, 150, 0.5f, 3.0f, setSpeedCallback, settings->getGameSpeed());
	volumeText = new Button("Volumen", 20, 100);
	volumeSlider = new Slider("Prueba", 30, 150, 150, 0, 128, setVolumeCallback, settings->getVolume());

	graphicsText = new Button("Graficos", 20, 80 + 120);
	wireFrameText = new Button("Wireframe", 30, 120 + 80 + 50,setWireframeCallback,"", true, settings->isWireframe());
	wireFrameText->center(30,230);
	texturesText = new Button("Textures", 30, 170 + 80 + 50,setTexturesCallback,"",true, settings->hasTextures());
	texturesText->center(30, 230);
	interpoladoText = new Button("Interpolado", 30, 220 + 80 + 50, setInterpoladoCallback,"",true,settings->hasFacetado());
	interpoladoText->center(30, 230);
	facetadoText = new Button("Facetado", 30, 270 + 80 + 50,  setFacetadoCallback,"",true,settings->hasInterpolado());
	facetadoText->center(30, 230);


	lightText = new Button("Luz",440, 20);
	lightDirText = new Button("Direccion", 450, 20 + 40);
	lightDirSlider = new Slider("", 460, 70 + 40, 150, 0, 2*M_PI, setLightAngleCallback, settings->getLightAngle());
	//TODO: agregar para seleccionar qu[e tipo de luz que cambi[as el color ambient, difuse,specular, usar el settings->setSelectedLight
	lightRText = new Button("Rojo", 450, 120 + 40);
	lightRSlider = new Slider("", 460, 160 + 40, 150, 0, 1, setLightRedCallback, settings->getLightColor().x);
	lightGText = new Button("Verde", 450, 220 + 40);
	lightGSlider = new Slider("", 460, 260 + 40, 150, 0, 1, setLightGreenCallback, settings->getLightColor().y);
	lightBText = new Button("Azul", 450, 320 + 40);
	lightBSlider = new Slider("", 460, 360 + 40, 150, 0, 1, setLightBlueCallback, settings->getLightColor().z);
	//lightAlphaText = new Button("Alfa", 450, 420 + 50);
	//lightAlphaSlider = new Slider("", 450, 460 + 50, 150, 0, 1, setLightAlphaCallback, settings->getLightAlpha());


	backToMenu = new Button("Volver al menu", 170, 440, goToMainMenuFromSettingsCallback, "", false,false);
	backToMenu->center(0, 640);
	backToGame = new Button("X", 640/2 - 8, 10, goBackToGameCallback,"", false,false);
	backToMenu->center(0, 640);
}

void SettingsMenu::changeGameSpeed(float speed)
{
	this->settings->setGameSpeed(speed);
}

void SettingsMenu::changeVolume(int volume)
{
	this->settings->setVolume(volume);
}

void SettingsMenu::setWireframe(bool wireframe)
{
	this->settings->setWireframe(wireframe);
}

void SettingsMenu::setTextures(bool texture)
{
	this->settings->setTextures(texture);
}

void SettingsMenu::setFacetado(bool val)
{
	settings->setFacetado(val);
}

void SettingsMenu::setInterpolado(bool val)
{
	settings->setInterpolado(val);
}

void SettingsMenu::setTexSettings(TEX_SETTINGS texSettings)
{
	this->settings->setTexSettings(texSettings);
}

void SettingsMenu::changeLightRed(float red)
{
	Vec3 currentLight = settings->getLightColor();
	float alpha = settings->getLightAlpha();
	settings->setLightColor({red,currentLight.y,currentLight.z},alpha);
}

void SettingsMenu::changeLightGreen(float green)
{
	Vec3 currentLight = settings->getLightColor();
	float alpha = settings->getLightAlpha();
	settings->setLightColor({ currentLight.x, green,currentLight.z },alpha);
}

void SettingsMenu::changeLightBlue(float blue)
{
	Vec3 currentLight = settings->getLightColor();
	float alpha = settings->getLightAlpha();
	settings->setLightColor({ currentLight.x,currentLight.y,blue },alpha);
}

void SettingsMenu::changeLightAngle(int angle)
{
	this->settings->setLightAngle(angle);
}

void SettingsMenu::changeLightAlpha(float alpha)
{
	printf("%f\n",alpha);
	Vec3 currentLight = settings->getLightColor();
	settings->setLightColor({ currentLight.x,currentLight.y,currentLight.z },alpha);
}

void SettingsMenu::goBackToGame()
{
	GameController::getInstance()->setState(GameController::getInstance()->getGamePlay());
	GameController::getInstance()->setPaused(false);
}

void SettingsMenu::goBackToMainMenu()
{
	if (GameController::getInstance()->getGamePlay() != NULL) {
		GamePlay* gp = GameController::getInstance()->getGamePlay();
		delete gp;
		GameController::getInstance()->setGamePlay(NULL);
	}
	GameController::getInstance()->setPaused(false);
	MainMenu* mm = new MainMenu();
	GameController::getInstance()->setState(mm);
}

void SettingsMenu::process(float deltaTime)
{
	if(GameController::getInstance()->getGamePlay() != NULL)
		GameController::getInstance()->getGamePlay()->draw(); //Only draw but don't process (Viborita can't move)
}

void SettingsMenu::draw()
{
}

std::vector<IHudElement*> SettingsMenu::getHudElements()
{
	std::vector<IHudElement*> buttons;
	buttons.push_back(speedText);
	buttons.push_back(speedSlider);
	buttons.push_back(volumeText);
	buttons.push_back(volumeSlider);
	buttons.push_back(wireFrameText);
	buttons.push_back(texturesText);
	if (GameController::getInstance()->getGamePlay() != NULL)
		buttons.push_back(backToGame);
	buttons.push_back(interpoladoText);
	buttons.push_back(facetadoText);
	buttons.push_back(backToMenu);
	buttons.push_back(lightDirText);
	buttons.push_back(lightDirSlider);
	buttons.push_back(lightRText);
	buttons.push_back(lightRSlider);
	buttons.push_back(lightGText);
	buttons.push_back(lightGSlider);
	buttons.push_back(lightBText);
	buttons.push_back(lightBSlider);
	buttons.push_back(graphicsText);
	buttons.push_back(lightText);
	//buttons.push_back(lightAlphaText); //No cambia nada en realidad
	//buttons.push_back(lightAlphaSlider);
	return buttons;
}