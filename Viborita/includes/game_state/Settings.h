#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <set>
#include "IGameState.h"

class Settings : public IGameState {
private:
	void changeGameSpeed();
	void toggleWireframe();
	void toggleTextures();
	void changeLightingSettings();
public:
	void process();
	set<int> getThingsToDraw();
};

#endif