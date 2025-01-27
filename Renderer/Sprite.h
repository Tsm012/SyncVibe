#pragma once
#include <SDL3/SDL.h>
class Sprite
{
public:
	unsigned int id = 0;
	SDL_Texture* texture;
	SDL_FRect boundingBox;
	int moveStep;
	Sprite();
	Sprite(unsigned int id, SDL_Texture* texture, const SDL_FRect& boundingBox, int moveStep);
private:
};


