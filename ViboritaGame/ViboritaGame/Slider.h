#pragma once
#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include <SDL_image.h>
#include "utils.h"

class Slider
{
private:
	std::string text;
	SDL_Rect* progressLine; //Estos dos son los dos rectangulos del slider:
	SDL_Rect* selector;		// 0 ------|---- 100
	bool movingSelector;
	float min;
	float max;
	void (*callback)(float newValue);
public:
	Slider(std::string text,int x, int y, int length, float min, float max, void (*callback)(float newValue));
	void draw();
	void mouseDownOnSelector();
	void mouseUp();
	void process();
};

