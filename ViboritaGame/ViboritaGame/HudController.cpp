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
    glPushMatrix();                    
    glLoadIdentity();
    glOrtho(0, 640, 480, 0, -1, 1);     
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();                     
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
    glPopMatrix();                      
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();                      
    glMatrixMode(GL_MODELVIEW);        
}

void HudController::setFont(TTF_Font* mainFont)
{
    this->mainFont = mainFont;
    Button::setFont(mainFont);
}

TTF_Font* HudController::getFont()
{
    return mainFont;
}
