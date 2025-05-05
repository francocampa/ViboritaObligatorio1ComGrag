#include "HudController.h"

HudController* HudController::instance = NULL;

HudController::HudController() {

}

HudController* HudController::getInstance()
{
	if (instance == NULL)
		instance = new HudController();

	return instance;
}

void HudController::process()
{
}
