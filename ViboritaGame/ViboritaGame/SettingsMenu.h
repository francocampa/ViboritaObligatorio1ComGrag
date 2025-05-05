#pragma once
#include "IGameState.h"
class SettingsMenu :
    public IGameState
{
private:
	void changeGameSpeed();
	void toggleWireframe();
	void toggleTextures();
	void changeLightingSettings();
public:
	void process();
	void draw();
};

