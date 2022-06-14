#include "Item.h"
Item::Item(float p_x, float p_y, SDL_Texture* p_tex)
	:x(p_x), y(p_y), tex(p_tex)
{
	count = 0;
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 100;
	currentFrame.h = 100;
}

float Item::getX()
{
	return x;
}
float Item::getY()
{
	return y;
}
int Item::getCount() 
{
	return count;
}
SDL_Texture* Item::getTex()
{
	return tex;
}

SDL_Rect Item::getCurrentFrame()
{
	return currentFrame;
}

void Item::setX(float x) {
	this->x = x;
}

void Item::setY(float y) {
	this->y = y;
}

void Item::setCount(int c) {
	count = c;
}

bool Item::isPressed(const SDL_Event* ev)
{
	if (ev->type == SDL_MOUSEBUTTONDOWN) {
		if (ev->button.button == SDL_BUTTON_LEFT &&
			ev->button.x >= x &&
			ev->button.x <= (x  + currentFrame.w) &&
			ev->button.y >= y  &&
			ev->button.y <= (y  + currentFrame.h)) {
			return true;
		}
	}
	return false;
}