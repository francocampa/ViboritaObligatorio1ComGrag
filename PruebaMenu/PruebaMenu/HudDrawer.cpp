#include "HudDrawer.h"

void goToLevel1() {

}
void goToLevel2() {

}

HudDrawer* HudDrawer::instance = NULL;

HudDrawer::HudDrawer()
{
    for (int i = 0; i < 10;i++) {
        buttons[i] = NULL;
    }
    buttons[0] = new Button("images/BtnLevel1.png", "images/BtnLevel1Hover.png", 100, 240, 200, 200, goToLevel1);
    buttons[1] = new Button("images/BtnLevel2.png","images/BtnLevel2Hover.png",350,240,200,200,goToLevel2);
}

HudDrawer* HudDrawer::getInstance()
{
    if (instance == NULL)
        instance = new HudDrawer();

    return instance;
}

void HudDrawer::drawHud(Vec2 mousePos,bool click)
{
    SDL_Rect mouse;
    mouse.h = 20;
    mouse.w = 20;
    mouse.x = mousePos.x;
    mouse.y = mousePos.y;

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();                     // Save current projection
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, -1, 1);     // Match SDL window coordinates
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();                     // Save modelview
    glLoadIdentity();
    int i = 0;
    for (Button * btn : buttons) {
        if (btn != NULL) {
            bool mouseOver = SDL_HasIntersection(&mouse, btn->getRect());
            if (mouseOver && click)
                btn->handleClick();
            if ((!mouseOver && btn->isHovering()) || (mouseOver && !btn->isHovering()))
                btn->handleHover();
            btn->draw();
            i++;
        }
    }
    printf("%d", i);
    glPopMatrix();                      // Restore modelview
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();                      // Restore projection
    glMatrixMode(GL_MODELVIEW);         // Back to 3D
}

