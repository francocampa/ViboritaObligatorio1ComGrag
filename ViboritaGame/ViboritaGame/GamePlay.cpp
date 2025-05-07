#include "GamePlay.h"

void openSettings() {
	printf("i wanna go to the settings pls");
}
GamePlay::GamePlay()
{
	settings = new Button("images/settings.png", "images/settingsHover.png", 580, 10, 50, 50, openSettings);
	scoreText = new Button("0/3",10,10,50,50);
	timerText = new Button("00:00",280,10,80,50);
}

void GamePlay::eatApple()
{
	GameStats* stats = GameController::getInstance()->getStats();

	stats->ateAnApple();
	int newScore = stats->getScore();
	int maxScore = stats->getMaxScore();

	std::string newText = std::to_string(newScore) + " / " + std::to_string(maxScore);

	scoreText->updateText(newText.c_str());

}

void GamePlay::changeTimer(const char* time)
{
	timerText->updateText(time);
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

std::vector<Button*> GamePlay::getHudButtons()
{
	std::vector<Button*> buttons;
	buttons.push_back(settings);
	buttons.push_back(scoreText);
	buttons.push_back(timerText);
	return buttons;
}
