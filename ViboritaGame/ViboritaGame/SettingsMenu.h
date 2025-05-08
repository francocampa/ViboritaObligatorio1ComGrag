#pragma once
#include "IGameState.h"
#include "Button.h"

class SettingsMenu :
    public IGameState
{
private:

	void changeGameSpeed();
	void toggleWireframe();
	void toggleTextures();
	void changeLightingSettings();
public:
	void process(float deltaTime);
	void draw();
	virtual std::vector<Button*> getHudButtons();
};

