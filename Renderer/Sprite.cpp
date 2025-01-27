#include "Sprite.h"
Sprite::Sprite() : texture(nullptr), boundingBox(SDL_FRect{ 100,100,100,100 }), moveStep(15)
{
}
Sprite::Sprite(unsigned int id, SDL_Texture* texture, const SDL_FRect& boundingBox, int moveStep)
	: texture(texture), boundingBox(boundingBox), moveStep(moveStep), id(id)
{
}
