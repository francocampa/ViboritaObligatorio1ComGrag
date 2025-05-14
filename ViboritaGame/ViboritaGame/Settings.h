#pragma once
#include "utils.h"
#include "GL/glu.h"

class Settings
{
private:
	float gameSpeed;
	bool wireframe;
	bool textures;
	TEX_SETTINGS texSettings;
	int lightAngle;
    Vec3 lightColor;
    float lightAlpha;
    GLenum SELECTED_LIGHT = GL_AMBIENT;
public:
	Settings();
	//Agregar getters y setters :D
    // Getters
    float getGameSpeed() const;
    bool isWireframe() const;
    bool hasTextures() const;
    TEX_SETTINGS getTexSettings() const;
    int getLightAngle() const;
    Vec3 getLightColor() const;
    float getLightAlpha() const;

    // Setters
    void setGameSpeed(float speed);
    void setWireframe(bool value);
    void setTextures(bool value);
    void setTexSettings(TEX_SETTINGS settings);
    void setLightAngle(int angle);
    void setLightColor(Vec3 color,float alpha);
    void setSelectedLight(GLenum light);
};

