#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <GL/glu.h>
#include "HudDrawer.h"

using namespace std;

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("ICG-UdelaR",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);
	IMG_Init(IMG_INIT_PNG);
	glMatrixMode(GL_PROJECTION);

	float color = 0;
	glClearColor(color, color, color, 1);

	gluPerspective(45, 640 / 480.f, 0.1, 100);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);

	bool fin = false;
	bool rotate = false;

	SDL_Event event;

	float x, y, z;

	x = 0;
	y = 0;
	z = 5;
	float degrees = 0;
	int mousex = 0;
	int mousey = 0;
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);


		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_MOUSEBUTTONDOWN:
				break;
			case SDL_MOUSEBUTTONUP:
				break;
			case SDL_QUIT:
				fin = true;
				break;
			case SDL_MOUSEMOTION:
				mousex = event.motion.x;
				mousey = event.motion.y;
			}
		}
		HudDrawer::getInstance()->drawHud({mousex,mousey});

		SDL_GL_SwapWindow(win);
	} while (!fin);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}