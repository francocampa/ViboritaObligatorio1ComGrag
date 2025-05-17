#include "LevelButton.h"

void calculatePreviewPos(Vec3 cameraPos, Vec3 center, int xOffset, float scale ,Vec3& previewPos) {

	//Normalized directions with respect to the vector from your face to the center of the viewport
	Vec3 forward = normalize({ center.x - cameraPos.x,center.y - cameraPos.y ,center.z - cameraPos.z });
	Vec3 right = normalize(crossProduct(forward, { 0,1,0 }));
	Vec3 up = normalize(crossProduct(right, forward));

	//Offsets
	float distance = 50 * scale;
	float yOffset = 0;

	previewPos = {
		cameraPos.x + forward.x * distance + right.x * xOffset + up.x * yOffset,
		cameraPos.y + forward.y * distance + right.y * xOffset + up.y * yOffset,
		cameraPos.z + forward.z * distance + right.z * xOffset + up.z * yOffset
	};
}

LevelButton::LevelButton(int x, Level* level,void(*callback)(std::string))
{
	this->level = level;
	this->rect = new SDL_Rect();
	this->x = x;
	switch (x)
	{
	case 0:
		rect->x = 50;
		break;
	case 1:
		rect->x = 640/2 - 75;
		break;
	case 2:
		rect->x = 640 - 150 - 50;
		break;
	default:
		break;
	}
	rect->y = 480/2 - 75;
	rect->h = 150;
	rect->w = 150;
	this->callback = callback;
	loadTextTexture(levelTextId,level->getName().c_str(),IHudElement::font,textSize.x,textSize.y);
}

void LevelButton::draw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glBegin(GL_QUADS);
	//glTexCoord2f(0.0f, 0.0f); glVertex2i(rect->x, rect->y);
	//glTexCoord2f(1.0f, 0.0f); glVertex2i(rect->x + rect->w, rect->y);
	//glTexCoord2f(1.0f, 1.0f); glVertex2i(rect->x + rect->w, rect->y + rect->h);
	//glTexCoord2f(0.0f, 1.0f); glVertex2i(rect->x, rect->y + rect->h);
	//glEnd();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glBindTexture(GL_TEXTURE_2D,levelTextId);
	glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			int offsetToCenterX = rect->w/2 - textSize.x/2;
			int x0 = offsetToCenterX + rect->x;
			int x1 = offsetToCenterX + rect->x + textSize.x;
			int y0 = rect->y + rect->h;
			int y1 = rect->y + rect->h + textSize.y;

			glTexCoord2f(0.0f, 0.0f); glVertex2i(x0,y0);
			glTexCoord2f(1.0f, 0.0f); glVertex2i(x1, y0);
			glTexCoord2f(1.0f, 1.0f); glVertex2i(x1, y1);
			glTexCoord2f(0.0f, 1.0f); glVertex2i(x0,y1);
		glEnd();
	glDisable(GL_TEXTURE_2D);

	IHudElement::goBackTo3d();
		Vec3 offset;
		int xOffset = x == 0 ? -16 : x == 1 ? 0 : 16;
		float scale = 1 + aProgress;
		calculatePreviewPos(GameController::getInstance()->getCameraPos(),{0,0,0},xOffset,tileScale, offset);
		glPushMatrix();
			glScalef(scale, scale, scale);
			glTranslatef(offset.x, offset.y, offset.z);
			glRotatef(angle,0,1,0);
			level->drawPreview(GameController::getInstance()->GRID_SIZE);
		glPopMatrix();
	IHudElement::goBackTo2d();
}

void LevelButton::process(float deltaTime)
{
	if (hover)
	{
		this->angle += 40 * deltaTime;
		if (this->aProgress < 0.3)
			this->aProgress += 2 * deltaTime;
	}
	else {
		if(this->aProgress > 0)
			this->aProgress -= 2 * deltaTime;
	}
}

BUTTON_TYPE LevelButton::getType()
{
	return LEVELBUTTON;
}

SDL_Rect* LevelButton::getRect()
{
	return rect;
}

void LevelButton::handleHover()
{
	this->hover = !hover;
}

bool LevelButton::isHovering()
{
	return hover;
}

void LevelButton::click()
{
	callback(level->getName());
}
