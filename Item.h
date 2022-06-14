#pragma once

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
class Item
{
public:
	Item(float p_x, float p_y, SDL_Texture* p_tex);
	float getX();
	float getY();
	int getCount();
	void setX(float x);
	void setY(float y);
	void setCount(int c);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();

	bool isPressed(const SDL_Event* ev);
private:
	float x, y;
	int count;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};

