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
    GameController* gc =  GameController::getInstance();
    Vec2 mousePos = gc->getMousePos();
    std::vector<IHudElement*> hud = gc->getHudElements();
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
    for (IHudElement* hudElement : hud) {
        bool mouseOver = SDL_HasIntersection(&mouse, hudElement->getRect());
        Button* btn;
        Slider* slider;
        switch (hudElement->getType())
        {
        case BUTTON:
            btn = (Button*)hudElement;
            if (mouseOver && gc->clicked())
                btn->handleClick();
            if ((!mouseOver && btn->isHovering()) || (mouseOver && !btn->isHovering()))
                btn->handleHover();
            break;
        case SLIDER:
            slider = (Slider*)hudElement;
            if (mouseOver && gc->isMouseDown())
                slider->mouseDown(mousePos);
            if (gc->isMouseUp())
                slider->mouseUp();

            slider->process(mousePos);           
            break;
        case CHECKBOX:
            break;
        default:
            break;
        }
        hudElement->draw();
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
