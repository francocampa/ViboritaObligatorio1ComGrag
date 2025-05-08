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
    // Getters
    float getGameSpeed() const;
    bool isWireframe() const;
    bool hasTextures() const;
    TEX_SETTINGS getTexSettings() const;
    float getLightAngle() const;
    Vec3 getLightColor() const;

    // Setters
    void setGameSpeed(float speed);
    void setWireframe(bool value);
    void setTextures(bool value);
    void setTexSettings(TEX_SETTINGS settings);
    void setLightAngle(float angle);
    void setLightColor(Vec3 color);
};

