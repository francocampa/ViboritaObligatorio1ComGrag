#pragma once
class GameStats
{
private:
	int score;
	int maxScore;
	int timerStartTime;
	bool levelAlreadyBeat;
public:
	GameStats(int maxScore,bool levelAlreadyBeat);
	void ateAnApple();
	void levelJustStarted();
	void beatLevel(int level);
	
	//Agregar getters
	int getScore();
	int getMaxScore();

};

