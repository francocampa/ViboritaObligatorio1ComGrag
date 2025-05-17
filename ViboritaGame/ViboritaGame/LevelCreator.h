#pragma once
#include "GameController.h"
#include "IGameState.h"
#include "IGameEntity.h"
#include "Viborita.h"
#include <filesystem>
#include "pugixml.hpp"
//#include "TextField.h"
//class TextField;
class LevelCreator :
    public IGameState
{
private:
    int noOfApples;
    std::string name;
    IGameEntity* grid[8][8][8];
    Viborita* viborita;
    Vec3 selectedGridIndex;
    GAME_ENTITY_TYPE selectedEntityType;

    TextField* nameField;
    Button* mainMenuButton;
    Button* saveButton;
    Button* clearButton;

    int selectedIndex = 0;
    IGameEntity* selectBar[8];
    Button* selectBarBoxes[8];
    float selectAngles[8];


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
    std::vector<IHudElement*> getHudElements();
    
    void setEntityTipe(GAME_ENTITY_TYPE type);
    void setErase(bool erase);
    void saveLevel();
    void clearGrid();
    void goBackToMainMenu();
    void setName(std::string name);
};

