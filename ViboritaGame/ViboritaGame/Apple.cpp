#include "Apple.h"

Apple::Apple(Vec3 gridIndexes, Vec3 position) : IGameEntity(gridIndexes,position) {
	this->angle = 0;
	this->movingUp = true;
	for (int i = 0; i < 12;i++) {
		int module = i % 3;
		int toAdd = 0;
		switch (module) {
		case 0:
			toAdd = position.x;
			break;
		case 1:
			toAdd = position.y;
			break;
		case 2:
			toAdd = position.z;
			break;
		}

		this->pyramid[i] = basePyramidVertices[i] + toAdd;
	}
}

void Apple::draw() {
	glColor3f(1, 1, 1);
	Material appleMaterial = { {0.8f, 0.8f, 0.8f, 1.0f} , {0.1f, 0.1f, 0.1f, 1.0f} ,  {0.4f, 0.4f, 0.4f, 1.0f}, {100.0f} };
	applyMaterial(appleMaterial);
	glPushMatrix();
	glTranslatef(this->pyramid[0] + 0.5f, this->pyramid[1], this->pyramid[2] + 0.5f);
	glScalef(0.2f, 0.2f, 0.2f);
	//glColor3f(1, 0.388f, 0.278f);//color rojo de las manzanas
	drawModel(APPLE_MODEL,GameController::getInstance()->getSettings()->hasTextures());
	glPopMatrix();
	applyMaterial(defaultMaterial);
	glColor3f(0, 0, 0);
}

void Apple::eatApple()
{
	playSound(CRUNCH);
	float TILESIZE = GameController::getInstance()->TILE_SIZE;
	ParticleSystem* ps = new ParticleSystem(0.001f, 0.3f, 50);
	ps->setLifeSpan(0.2f,0.2f);
	ps->setVelocityRange({ -0.03,0.01f,-0.03 }, { 0.05,0.05f,0.05 });
	ps->setAccelerationRange({ 0,-0.1f,0 }, { 0,-0.1,0 });
	ps->setPosRange({ position.x,position.y,position.z}, { position.x + TILESIZE, position.y + TILESIZE, position.z + TILESIZE });
	ps->setAlphaRange(0.5f, 1);
	ps->setColorRange({ 0.3f,0,0 }, { 0.7f,0,0 });
	ps->setSizeRange(4, 8);
	GameController::getInstance()->addParticles(ps);
}

GAME_ENTITY_TYPE Apple::getType()
{
	return APPLE;
}

void Apple::process(float deltaTime) {
	float movement = deltaTime * 0.5f;
	if (movingUp) {
		this->pyramid[1] += movement;
		this->pyramid[4] += movement;
		this->pyramid[7] += movement;
		this->pyramid[10] += movement;
	}
	else {
		this->pyramid[1] -= movement;
		this->pyramid[4] -= movement;
		this->pyramid[7] -= movement;
		this->pyramid[10] -= movement;
	}

	if (this->pyramid[10] > position.y+1.5f) {
		movingUp = false;
	}
	else if (this->pyramid[10] < position.y+1.0f) {
		movingUp = true;
	}
	
	this->angle += 0.5f;
}