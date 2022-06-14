#include "Button.h"

Button::Button(float p_x, float p_y, SDL_Texture* p_tex)
	:x(p_x), y(p_y), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 400;
	currentFrame.h = 100;
}

float Button::getX()
{
	return x;
}
float Button::getY()
{
	return y;
}

SDL_Texture* Button::getTex()
{
	return tex;
}

SDL_Rect Button::getCurrentFrame()
{
	return currentFrame;
}

void Button::setX(float x) {
	this->x = x;
}

void Button::setY(float y) {
	this->y = y;
}

bool Button::isPressed(const SDL_Event* ev)
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