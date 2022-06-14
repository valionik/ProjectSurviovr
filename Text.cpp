#include "Text.h"
#include <iostream>

Text::Text(SDL_Renderer* renderer, const string& font_path, int font_size, const string& message_text, const SDL_Color& color)
{
	_text_texture = loadFont(renderer, font_path, font_size, message_text, color);
	SDL_QueryTexture(_text_texture, nullptr, nullptr, &_text_rect.w, &_text_rect.h);

}

void Text::display(float x, float y, SDL_Renderer* renderer)
{
	_text_rect.x = x;
	_text_rect.y = y;
	SDL_RenderCopy(renderer, _text_texture,nullptr, &_text_rect);
}

SDL_Texture* Text::loadFont(SDL_Renderer *renderer, const string& font_path, int font_size, const string& message_text, const SDL_Color& color)
{
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
	if (!font) cout << "failed to load font" << endl;
	auto text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
	if (!text_surface) cout << "failed to create surface" << endl;
	auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
	if (!text_texture) cout << "failed to create text texture" << endl;

	SDL_FreeSurface(text_surface);
	TTF_CloseFont(font);
	return text_texture;

}
void Text::cleanUp()
{
	SDL_DestroyTexture(_text_texture);
}