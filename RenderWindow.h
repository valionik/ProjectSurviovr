#pragma once

#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>

#include "Entity.h"
#include "Button.h"
#include "Placeholder.h"
#include "Item.h"
#include "IslandButton.h"


class RenderWindow
{
public:
	//constructor
	RenderWindow(const char* p_title, int p_w, int p_h);
	//destructor
	void cleanUp();

	SDL_Texture* loadTexture(const char* p_filePath);

	int getRefreshRate();

	void clear();
	void renderTexture(SDL_Texture* p_tex);
	void renderEntity(Entity& p_entity);
	void renderButton(Button& p_button);
	void renderIslandButton(IslandButton& p_button);
	void renderPlaceholder(Placeholder& p_placeholder);
	void renderItem(Item& p_item);
	void display();

	SDL_Renderer* getRenderer();
private:
	//declare adresses of window and renderer
	SDL_Window* window;
	SDL_Renderer* renderer;
};

