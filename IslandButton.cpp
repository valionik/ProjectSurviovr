#include "IslandButton.h"

IslandButton::IslandButton(float p_x, float p_y, SDL_Texture* p_tex)
	:x(p_x), y(p_y), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 200;
	currentFrame.h = 50;
}

float IslandButton::getX()
{
	return x;
}
float IslandButton::getY()
{
	return y;
}

SDL_Texture* IslandButton::getTex()
{
	return tex;
}

SDL_Rect IslandButton::getCurrentFrame()
{
	return currentFrame;
}

void IslandButton::setX(float x) {
	this->x = x;
}

void IslandButton::setY(float y) {
	this->y = y;
}

bool IslandButton::isPressed(const SDL_Event* ev)
{
	if (ev->type == SDL_MOUSEBUTTONDOWN) {
		if (ev->button.button == SDL_BUTTON_LEFT &&
			ev->button.x >= x &&
			ev->button.x <= (x + currentFrame.w) &&
			ev->button.y >= y &&
			ev->button.y <= (y + currentFrame.h)) {
			return true;
		}
	}
	return false;
}