#pragma once
#include "utils.h"
#include <set>
#include "Button.h"

class HudDrawer
{
private:
	Button* buttons[10];
	HudDrawer();
	static HudDrawer* instance;
public:
	static HudDrawer* getInstance();
	void drawHud(Vec2 mousePos);
};

