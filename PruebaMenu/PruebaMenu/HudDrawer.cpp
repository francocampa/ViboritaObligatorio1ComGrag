#include "HudDrawer.h"

HudDrawer* HudDrawer::instance = NULL;
HudDrawer::HudDrawer()
{
    for (int i = 0; i < 10;i++) {
        buttons[i] = NULL;
    }
    buttons[0] = new Button();
}

HudDrawer* HudDrawer::getInstance()
{
    if (instance == NULL)
        instance = new HudDrawer();

    return instance;
}

void HudDrawer::drawHud(Vec2 mousePos)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();                     // Save current projection
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, -1, 1);     // Match SDL window coordinates
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();                     // Save modelview
    glLoadIdentity();

    for (Button * btn : buttons) {
        if (btn != NULL)
            btn->draw();
    }

    glPopMatrix();                      // Restore modelview
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();                      // Restore projection
    glMatrixMode(GL_MODELVIEW);         // Back to 3D
}


