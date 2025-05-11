#pragma once
#include "GameController.h"
#include "IGameEntity.h"
#include "utils.h"

class Apple :
    public IGameEntity
{
private:
    bool movingUp;
    float angle;
    GLfloat pyramid[12];
public:
    Apple(Vec3 gridIndexes, Vec3 position);
    void process(float deltaTime);
    void draw();
    GAME_ENTITY_TYPE getType();
};

