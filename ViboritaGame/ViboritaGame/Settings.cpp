#include "Settings.h"

Settings::Settings()
{
	//Setear configs por defecto
	this->gameSpeed = 1;
	this->textures = true;
	this->wireframe = false;
	this->texSettings = INTERPOLADO;
    this->lightColor = { 1,1,1 };
    this->lightAngle = 0;
}

float Settings::getGameSpeed() const {
    return gameSpeed;
}

bool Settings::isWireframe() const {
    return wireframe;
}

bool Settings::hasTextures() const {
    return textures;
}

TEX_SETTINGS Settings::getTexSettings() const {
    return texSettings;
}

int Settings::getLightAngle() const {
    return lightAngle;
}

Vec3 Settings::getLightColor() const {
    return lightColor;
}

void Settings::setGameSpeed(float speed) {
    gameSpeed = speed;
}

void Settings::setWireframe(bool value) {
    wireframe = value;
}

void Settings::setTextures(bool value) {
    textures = value;
}

void Settings::setTexSettings(TEX_SETTINGS settings) {
    texSettings = settings;
}

void Settings::setLightAngle(int angle) {
    lightAngle = angle;
}

void Settings::setLightColor(Vec3 color) {
    lightColor = color;
}