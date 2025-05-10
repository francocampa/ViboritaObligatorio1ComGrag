#pragma once
#include "GameController.h"
#include "IGameState.h"
#include "IGameEntity.h"
#include "Viborita.h"
#include <filesystem>

class LevelCreator :
    public IGameState
{
private:
    static int autoId;

    IGameEntity* grid[8][8][8];
    Viborita* viborita;
    Vec3 selectedGridIndex;
    GAME_ENTITY_TYPE selectedEntityType;

    Button* blockButton;
    Button* appleButton;
    Button* goalButton;
    Button* viboritaButton;
    Button* erasorButton;
    Button* saveButton;
    Button* clearButton;
    Button* mainMenuButton;

    bool erase;

    bool fill;
    Vec3 fillOrigin;

    void createButtons();
    void handleSelectedIndexMovement();
    void handlePlaceEntity();
public:
    LevelCreator();
    void process(float deltaTime);
    void draw();
    std::vector<Button*> getHudButtons();
    
    void setEntityTipe(GAME_ENTITY_TYPE type);
    void setErase(bool erase);
    void saveLevel();
    void clearGrid();
    void goBackToMainMenu();
};

