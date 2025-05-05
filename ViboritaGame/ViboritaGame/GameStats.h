#pragma once
class GameStats
{
private:
	int score;
	int timerStartTime;
	bool levelAlreadyBeat;
public:
	GameStats();
	void ateAnApple();
	void levelJustStarted();
	void beatLevel(int level);
	//Agregar getters
};

