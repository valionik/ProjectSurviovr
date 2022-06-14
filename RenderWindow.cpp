#include "RenderWindow.h"

using namespace std;

//define constructor
RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h):window(NULL), renderer(NULL)
{
	//define the window
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
	
	if (window == NULL) cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	
	//if there is a graphic card, use it (for faster runtime)
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL) cout << "Failed to load texture. Error: " << SDL_GetError() << endl; 
	
	return texture;
}

int RenderWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex(window);
	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}

void RenderWindow::cleanUp() {
	SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
	SDL_RenderClear(renderer);
}

void RenderWindow::renderTexture(SDL_Texture* p_tex) {
	SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}

void RenderWindow::renderEntity(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX();
	dst.y = p_entity.getY();
	dst.w = p_entity.getCurrentFrame().w ;
	dst.h = p_entity.getCurrentFrame().h ;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::renderButton(Button& p_button) 
{
	SDL_Rect src;
	src.x = p_button.getCurrentFrame().x;
	src.y = p_button.getCurrentFrame().y;
	src.w = p_button.getCurrentFrame().w;
	src.h = p_button.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_button.getX();
	dst.y = p_button.getY();
	dst.w = p_button.getCurrentFrame().w ;
	dst.h = p_button.getCurrentFrame().h;

	SDL_RenderCopy(renderer, p_button.getTex(), &src, &dst);
}

void RenderWindow::renderIslandButton(IslandButton& p_button)
{
	SDL_Rect src;
	src.x = p_button.getCurrentFrame().x;
	src.y = p_button.getCurrentFrame().y;
	src.w = p_button.getCurrentFrame().w;
	src.h = p_button.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_button.getX();
	dst.y = p_button.getY();
	dst.w = p_button.getCurrentFrame().w;
	dst.h = p_button.getCurrentFrame().h;

	SDL_RenderCopy(renderer, p_button.getTex(), &src, &dst);
}

void RenderWindow::renderPlaceholder(Placeholder& p_placeholder) 
{
	SDL_Rect src;
	src.x = p_placeholder.getCurrentFrame().x;
	src.y = p_placeholder.getCurrentFrame().y;
	src.w = p_placeholder.getCurrentFrame().w;
	src.h = p_placeholder.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_placeholder.getX();
	dst.y = p_placeholder.getY();
	dst.w = p_placeholder.getCurrentFrame().w/1.6;
	dst.h = p_placeholder.getCurrentFrame().h/1.6;

	SDL_RenderCopy(renderer, p_placeholder.getTex(), &src, &dst);

}

void RenderWindow::renderItem(Item& p_item) 
{
	SDL_Rect src;
	src.x = p_item.getCurrentFrame().x;
	src.y = p_item.getCurrentFrame().y;
	src.w = p_item.getCurrentFrame().w;
	src.h = p_item.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_item.getX();
	dst.y = p_item.getY();
	dst.w = p_item.getCurrentFrame().w/1.2 ;
	dst.h = p_item.getCurrentFrame().h/1.2 ;

	SDL_RenderCopy(renderer, p_item.getTex(), &src, &dst);

}



void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::getRenderer() {
	return renderer;
}