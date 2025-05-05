#pragma once
#include <iostream>

class HudController
{
private:
	static HudController* instance;
	HudController();
public:
	static HudController* getInstance();
	void process(); //Draw hud and check for button clicks
};

