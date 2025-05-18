#include "Cloud.h"

//TODO: agregar alturas variables
Cloud::Cloud(int type, float radio, float angle){
	this->type = type;
	this->position = {0,0,0};
	this->angle = angle;
	this->angleSpeed = 0.0001f;
	this->radio = radio;
};

void Cloud::draw() {
	glPushMatrix();
	this->angle += this->angleSpeed;
	position.x = 12 * cos(this->angle);
	position.y = 0; 
	position.z = 12 * sin(this->angle);
	Material cloudMaterial = { {0.8f, 0.8f, 0.8f, 1.0f} , {0.1f, 0.1f, 0.1f, 1.0f} ,  {0.4f, 0.4f, 0.4f, 1.0f}, {100.0f} };
	applyMaterial(cloudMaterial);
	glTranslatef(position.x, position.y, position.z);
	glScalef(1, 0.5, 1);
	glColor3f(0.255, 0.255, 0.255);
	switch (this->type) {
	case 1:
		drawModel(CLOUD1_MODEL, false);
		break;
	case 2:
		drawModel(CLOUD2_MODEL, false);
		break;
	case 3:
		drawModel(CLOUD3_MODEL, false);
		break;
	}
	applyMaterial(defaultMaterial);
	glPopMatrix();
};

GAME_ENTITY_TYPE Cloud::getType() {
	return CLOUD;
};

void Cloud::setCloudAngle(float angle) {
	this->angle = angle;
};