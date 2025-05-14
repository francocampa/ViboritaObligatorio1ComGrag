#include "utils.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#include <iostream>
#include <GL/glu.h>
#include <iostream>
#include "GameController.h"
#include "LevelCreator.h"


void calculateArrowKeysPos(Vec3 cameraPos, Vec3 center, Vec3& arrowKeyPos) {
	
	//Normalized directions with respect to the vector from your face to the center of the viewport
	Vec3 forward = normalize({ center.x - cameraPos.x,center.y - cameraPos.y ,center.z - cameraPos.z });
	Vec3 right = normalize(crossProduct(forward,{0,1,0}));
	Vec3 up = normalize(crossProduct(right, forward));

	//Offsets
	float distance = 30;
	float xOffset = 12;
	float yOffset = -10;

	arrowKeyPos = {
		cameraPos.x + forward.x*distance + right.x*xOffset + up.x*yOffset,
		cameraPos.y + forward.y * distance + right.y * xOffset + up.y * yOffset,
		cameraPos.z + forward.z * distance + right.z * xOffset + up.z * yOffset
	};
}


void setupLighting() {
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_NORMALIZE);

	GLfloat lightPos[] = { 0.0f, 10.0f, 10.0f, 0.0f }; // Last value: 1.0 = positional, 0.0 = directional
	GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	
}


int WINDOW_WIDTH = 640;
int WINDOW_HEIGHT = 480;

using namespace std;
int main(int argc, char* argv[]) {
	//void main() {

	//	Init sld
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		exit(1);
	}

	SDL_Window* win = SDL_CreateWindow("Viborita",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	SDL_GLContext context = SDL_GL_CreateContext(win);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	TTF_Font* mainFont = TTF_OpenFont("fonts/Sans Serif Shaded.ttf", 32);
	if (mainFont == NULL)
		printf("Failed to load font");
	HudController::getInstance()->setFont(mainFont);

	if (glewInit() != GLEW_OK)
	{
		// Manejar error de inicialización de GLEW
		return -1;
	}

	//Camera setup
	glMatrixMode(GL_PROJECTION);

	glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
	gluPerspective(45, WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1, 100);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

	GameController::getInstance()->setState(new MainMenu());
	Settings* settings = new Settings();
	GameController::getInstance()->setSettings(settings);

	//Carga de modelos
	std::string filePath = "models/apple.obj";
	std::string name = "apple";
	GLuint textureID;
	cargarModelo(filePath, name, 0);// Se le pasa el filePath, el nombre del modelo y la posición que ocupará en el modelsInfo
	loadTexture(textureID, "images/restart.png");//Por ahora hay una textura random
	modelsInfo[0].textureId = textureID;
	filePath = "models/worm_head.obj";
	name = "wormHead";
	cargarModelo(filePath, name, 1);
	filePath = "models/worm_body.obj";
	name = "wormBody";
	cargarModelo(filePath, name, 2);
	filePath = "models/worm_tail.obj";
	name = "wormTail";
	cargarModelo(filePath, name, 3);
	filePath = "models/portal.obj";
	name = "portal";
	cargarModelo(filePath, name, 4);

	bool quit = false;
	bool moveCamera = false;
	bool rotate = false;
	bool alreadyMoved = false;
	bool paused = false;
	int speed = 1;
	SDL_Event event;
	float cameraVel = 0.1f;
	float cameraAngle = 0.0;
	Vec3 cameraPos = { 0,0,30 };
	Vec3 center = { 0,0,0 };
	float objDistance = distance(cameraPos, center);
	Uint64 currentTick = SDL_GetPerformanceCounter();
	Uint64 lastTick = currentTick;
	float degrees = 0;
	float cameraRadius = 20;

	GLfloat cubever[24];
	for (int i = 0;i < 24;i++) {
		cubever[i] = baseCubeVertices[i] + 1;
	}
	float theta = 0;
	float phi = M_PI / 2;
	float sensitivity = 0.5f;

	float sunAngle = 0;

	cameraPos.x = cameraRadius * sin(phi) * cos(theta);
	cameraPos.y = cameraRadius * cos(phi);
	cameraPos.z = cameraRadius * sin(phi) * sin(theta);

	Vec3 arrowKeysPos = { 0,0,0 };

	calculateArrowKeysPos(cameraPos,center, arrowKeysPos);

	float timeFromDown = 100;
	float CLICK_TIME = 0.8f;

	setupLighting();

	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		currentTick = SDL_GetPerformanceCounter();

		float deltaTime = (currentTick - lastTick) / (float)SDL_GetPerformanceFrequency();
		deltaTime *= settings->getGameSpeed();
		lastTick = currentTick;
		timeFromDown += deltaTime/settings->getGameSpeed();

		//son 3 vector3, donde me paro, donde miro, y donde est[a arriba
		gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, center.x, center.y, center.z, 0, 1, 0);
		if(!paused)
			GameController::getInstance()->processFrame(deltaTime);

		GameController::getInstance()->setArrowRight(false);
		GameController::getInstance()->setArrowLeft(false);
		GameController::getInstance()->setArrowDown(false);
		GameController::getInstance()->setArrowUp(false);
		GameController::getInstance()->setZKey(false);
		GameController::getInstance()->setXKey(false);
		GameController::getInstance()->setClick(false);
		GameController::getInstance()->setMouseUp(false);
		GameController::getInstance()->setSpaceKey(false);

		drawArrowKeys({ arrowKeysPos.x-1.7f,arrowKeysPos.y,arrowKeysPos.z });
		/*glPointSize(10.0f); //Debug arrow center jiji
		glBegin(GL_POINTS);
		glColor3f(0, 1, 0);
		glVertex3f(arrowKeysPos.x, arrowKeysPos.y, arrowKeysPos.z);
		glEnd();
		glColor3f(1, 1, 1);*/

		glPushMatrix();
		glRotatef(120,0,1.0f,1.0f);
		sunAngle += deltaTime * 1.0f;
		GLfloat lightPos[] = { 10.0f*cos(sunAngle), 10.0f*sin(sunAngle), 0.0f, 0.0f}; // Last value: 1.0 = positional, 0.0 = directional
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		
		glPopMatrix();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
					case SDLK_p:
						paused = !paused;
						printf(paused ? "pausado" : "despausao");
						break;
					case SDLK_ESCAPE:
						quit = true;
						break;
					case SDLK_UP:
					case SDLK_DOWN:
					case SDLK_LEFT:
					case SDLK_RIGHT:
					case SDLK_x:
					case SDLK_z:
					case SDLK_SPACE:
						alreadyMoved = false;
						break;
					case SDLK_d:
						GameController::getInstance()->setShowFps(!GameController::getInstance()->isShowFps());
						break;
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
				case SDLK_z:
					GameController::getInstance()->setZKey(true);
					alreadyMoved = true;
					break;
				case SDLK_x:
					GameController::getInstance()->setXKey(true);
					alreadyMoved = true;
					break;
				case SDLK_SPACE:
					GameController::getInstance()->setSpaceKey(true);
					alreadyMoved = true;
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				moveCamera = true;
				timeFromDown = 0.0f;
				GameController::getInstance()->setMouseDown(true);
				SDL_SetRelativeMouseMode(SDL_TRUE);
				break;
			case SDL_MOUSEBUTTONUP:
				moveCamera = false;
				if(timeFromDown <= CLICK_TIME)
					GameController::getInstance()->setClick(true);
				GameController::getInstance()->setMouseUp(true);
				GameController::getInstance()->setMouseDown(false);
				SDL_SetRelativeMouseMode(SDL_FALSE);
				break;
			case SDL_MOUSEMOTION:
				GameController::getInstance()->setMousePos({ event.motion.x, event.motion.y });
				if (moveCamera) {
					int deltaX = event.motion.xrel;
					int deltaY = event.motion.yrel;

					/*int horDir = deltaX != 0 ? deltaX / abs(deltaX) : 0;
					int verDir = deltaY != 0 ? deltaY / abs(deltaY) : 0;*/ //Noble but flawed idea sadly :c

					theta += sensitivity * deltaTime * deltaX;
					phi += sensitivity * sin(deltaTime * deltaY);

					float epsilon = 0.5f;
					if (phi < epsilon) phi = epsilon;
					if (phi > M_PI - epsilon) phi = M_PI - epsilon;

					cameraPos.x = cameraRadius * sin(phi) * cos(theta);
					cameraPos.y = cameraRadius * cos(phi);
					cameraPos.z = cameraRadius * sin(phi) * sin(theta);

					calculateArrowKeysPos(cameraPos, center, arrowKeysPos);
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
	TTF_CloseFont(mainFont);
	SDL_Quit();
	return 0;
}




