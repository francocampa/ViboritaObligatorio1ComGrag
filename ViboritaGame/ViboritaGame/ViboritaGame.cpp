#include <SDL.h>
#include <SDL_opengl.h>
#include <iostream>
#include <GL/glu.h>
#include <iostream>
#include "utils.h"
#include "GameController.h"

int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;

using namespace std;
int main(int argc, char* argv[]) {
	//void main() {

	//	Init sld
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("Prueba grid",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);

	//Camera setup
	SDL_SetRelativeMouseMode(SDL_TRUE);
	glMatrixMode(GL_PROJECTION);

	glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
	gluPerspective(45, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1, 100);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

	bool quit = false;
	bool move = false;
	bool rotate = false;
	bool alreadyMoved = false;
	int speed = 1;
	SDL_Event event;
	float cameraVel = 0.1f;
	float cameraAngle = 0.0;
	Vec3 cameraPos = { 0,0,30 };
	Vec3 center = { 0,0,0 };
	float objDistance = distance(cameraPos, center);
	Uint64 currentTime = SDL_GetPerformanceCounter();
	Uint64 lastTime = currentTime;
	float degrees = 0;
	float cameraRadius = 20;

	GLfloat cubever[24];
	for (int i = 0;i < 24;i++) {
		cubever[i] = baseCubeVertices[i] + 1;
	}
	float theta = 0;
	float phi = M_PI / 2;

	cameraPos.x = cameraRadius * sin(phi) * cos(theta);
	cameraPos.y = cameraRadius * cos(phi);
	cameraPos.z = cameraRadius * sin(phi) * sin(theta);
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		
		currentTime = SDL_GetPerformanceCounter();
		float deltaTime = (currentTime - lastTime) / (float)SDL_GetPerformanceFrequency();
		lastTime = currentTime;

		//son 3 vector3, donde me paro, donde miro, y donde est[a arriba
		gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, center.x, center.y, center.z, 0, 1, 0);
		GameController::getInstance()->processFrame(deltaTime);
		GameController::getInstance()->setArrowRight(false);
		GameController::getInstance()->setArrowLeft(false);
		GameController::getInstance()->setArrowDown(false);
		GameController::getInstance()->setArrowUp(false);
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_UP:
				case SDLK_DOWN:
				case SDLK_LEFT:
				case SDLK_RIGHT:
					alreadyMoved = false;
				}
				break;
			case SDL_KEYDOWN:
				if (alreadyMoved)
					break;
				

				switch (event.key.keysym.sym) {
				case SDLK_UP:
					GameController::getInstance()->setArrowUp(true);
					alreadyMoved = true;
					break;
				case SDLK_DOWN:
					GameController::getInstance()->setArrowDown(true);
					alreadyMoved = true;
					break;
				case SDLK_LEFT:
					GameController::getInstance()->setArrowLeft(true);
					alreadyMoved = true;
					break;
				case SDLK_RIGHT:
					GameController::getInstance()->setArrowRight(true);
					alreadyMoved = true;
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				move = true;
				break;
			case SDL_MOUSEBUTTONUP:
				move = false;
				break;
			case SDL_MOUSEMOTION:
				if (move) {
					int deltaX = event.motion.xrel;
					int deltaY = event.motion.yrel;

					int horDir = deltaX != 0 ? deltaX / abs(deltaX) : 0;
					int verDir = deltaY != 0 ? deltaY / abs(deltaY) : 0;

					theta += deltaTime * horDir;
					phi += sin(deltaTime * verDir);

					float epsilon = 0.5f;
					if (phi < epsilon) phi = epsilon;
					if (phi > M_PI - epsilon) phi = M_PI - epsilon;

					// Convert spherical to Cartesian coordinates
					cameraPos.x = cameraRadius * sin(phi) * cos(theta);
					cameraPos.y = cameraRadius * cos(phi);
					cameraPos.z = cameraRadius * sin(phi) * sin(theta);

				}

				break;
			case SDL_MOUSEWHEEL:
				int scrollY = event.wheel.y;
				if (scrollY != 0) {
					float movement = deltaTime * speed * 20 * (scrollY / abs(scrollY));
					cameraRadius += -movement;
					if (cameraRadius < 0.5 || cameraRadius > 40)
						cameraRadius += movement;


					cameraPos.x = cameraRadius * sin(phi) * cos(theta);
					cameraPos.y = cameraRadius * cos(phi);
					cameraPos.z = cameraRadius * sin(phi) * sin(theta);
				}

				break;
			}

		}

		SDL_GL_SwapWindow(win);
	} while (!quit);

	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}




