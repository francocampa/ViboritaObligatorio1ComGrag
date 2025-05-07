#include "GamePlay.h"

void GamePlay::handleSnakeMovement()
{
}

void GamePlay::eatApple()
{
}

void GamePlay::beatLevel()
{
}

void GamePlay::resetLevel()
{
}

void GamePlay::process()
{
}

void GamePlay::draw()
{
}

void openSettings() {
	printf("i wanna go to the settings pls");
}

std::vector<Button*> GamePlay::getHudButtons()
{
	std::vector<Button*> buttons;
	Button* settings = new Button("images/settings.png","images/settingsHover.png",580, 10, 50,50,openSettings);
	buttons.push_back(settings);
	return buttons;
}
