#pragma once
#include "Button.h"
#include "GameController.h"
#include "IGameState.h"
#include "Settings.h"
#include "Slider.h"

class SettingsMenu :
    public IGameState
{
private:
	Settings* settings;

	Button* speedText;
	Slider* speedSlider;

	Button* wireFrameText;
	Button* wireFrameTrue;
	Button* wireFrameFalse;

	Button* texturesText;
	Button* texturesTrue;
	Button* texturesFalse;

	Button* backToGame;
	Button* backToMenu;

	Button* interpoladoText;
	Button* interpoladoCheck;
	Button* facetadoText;
	Button* facetadoCheck;
	
	Button* lightDirText;
	Slider* lightDirSlider;
public:
	SettingsMenu(Settings* settings);
	void process(float deltaTime);
	void draw();
	void changeGameSpeed(float gameSpeed);
	void setWireframe(bool wireframe);
	void setTextures(bool texture);
	void setTexSettings(TEX_SETTINGS texSettings);
	void changeLightAngle(int angle);
	void goBackToGame();
	void goBackToMainMenu();
	virtual std::vector<IHudElement*> getHudElements();
};

