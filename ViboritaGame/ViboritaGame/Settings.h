#pragma once
#include "utils.h"

class Settings
{
private:
	float gameSpeed;
	bool wireframe;
	bool textures;
	TEX_SETTINGS texSettings;
	float lightAngle;
	Vec3 lightColor;
public:
	Settings();
	//Agregar getters y setters :D
};

