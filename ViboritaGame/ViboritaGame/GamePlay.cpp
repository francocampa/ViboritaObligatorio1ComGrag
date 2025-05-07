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

void GamePlay::changeTimer(int time)
{
	int minutes = time / 60;
	int seconds = time - minutes * 60;
	std::string mString = minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes);
	std::string sString = seconds < 10 ? "0"+std::to_string(seconds) : std::to_string(seconds) ;
	std::string text = mString + ":"+ sString;
	timerText->updateText(text.c_str());
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
