#include "HudController.h"

HudController* HudController::instance = NULL;

HudController::HudController() {

}

HudController* HudController::getInstance()
{
	if (instance == NULL)
		instance = new HudController();

	return instance;
}

void HudController::process()
{
    Vec2 mousePos = GameController::getInstance()->getMousePos();
    std::vector<Button*> buttons = GameController::getInstance()->getHudButtons();
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (Button* btn : buttons) {
        if (btn != NULL) {
            bool mouseOver = SDL_HasIntersection(&mouse, btn->getRect());
            if (mouseOver && GameController::getInstance()->clicked())
                btn->handleClick();
            if ((!mouseOver && btn->isHovering()) || (mouseOver && !btn->isHovering()))
                btn->handleHover();
            btn->draw();
        }
    }
    glDisable(GL_BLEND);
    glPopMatrix();                      // Restore modelview
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();                      // Restore projection
    glMatrixMode(GL_MODELVIEW);         // Back to 3D
}
