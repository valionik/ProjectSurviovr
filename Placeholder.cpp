#include "Placeholder.h"

Placeholder::Placeholder(float p_x, float p_y, SDL_Texture* p_tex)
	:x(p_x), y(p_y), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 256;
	currentFrame.h = 256;
}

float Placeholder::getX()
{
	return x;
}
float Placeholder::getY()
{
	return y;
}

SDL_Texture* Placeholder::getTex()
{
	return tex;
}

SDL_Rect Placeholder::getCurrentFrame()
{
	return currentFrame;
}

void Placeholder::setX(float x) {
	this->x = x;
}

void Placeholder::setY(float y) {
	this->y = y;
}

bool Placeholder::isPressed(const SDL_Event* ev)
{
	if (ev->type == SDL_MOUSEBUTTONDOWN) {
		if (ev->button.button == SDL_BUTTON_LEFT &&
			ev->button.x >= x  &&
			ev->button.x <= (x  + currentFrame.w/1.6) &&
			ev->button.y >= y  &&
			ev->button.y <= (y  + currentFrame.h/1.6)) {
			return true;
		}
	}
	return false;
}