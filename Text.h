#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

using namespace std;
class Text
{
public:
	Text(SDL_Renderer* renderer, const string &font_path, int font_size, const string& message_text, const SDL_Color &color);
	void cleanUp();
	void display(float x, float y, SDL_Renderer* renderer);
	static SDL_Texture* loadFont(SDL_Renderer* renderer, const string& font_path, int font_size, const string& message_text, const SDL_Color& color);

private:
	SDL_Texture* _text_texture = nullptr;
	SDL_Rect _text_rect;
};

