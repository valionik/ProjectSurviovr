#pragma once

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

class Entity
{
public:
	Entity(float p_x, float p_y, SDL_Texture* p_tex);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
	SDL_Texture* getTex();
	SDL_Rect getCurrentFrame();
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};