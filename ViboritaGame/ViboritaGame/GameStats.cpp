#include "GameStats.h"

GameStats::GameStats(int maxScore, bool levelAlreadyBeat)
{
	this->score = 0;
	this->maxScore = maxScore;
	this->levelAlreadyBeat = levelAlreadyBeat;
	this->timerStartTime = 0;
}

void GameStats::ateAnApple()
{
	this->score++;
}

void GameStats::levelJustStarted()
{
	
}

void GameStats::beatLevel(int level)
{
}

int GameStats::getScore()
{
	return score;
}

int GameStats::getMaxScore()
{
	return maxScore;
}
