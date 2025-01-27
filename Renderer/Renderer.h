#pragma once
#include <iostream>
#include <vector>
#include "Sprite.h"
#include <unordered_map>

class UI
{
public:
	bool initialize(std::string title);
	SDL_Event getInput();
	void cleanup(std::unordered_map<unsigned int, Sprite> players, std::unordered_map<unsigned int, Sprite> gameObjects);
	void render(std::unordered_map<unsigned int, Sprite> players, std::unordered_map<unsigned int, Sprite> gameObjects);

	// Function to load texture from BMP file
	SDL_Texture* loadTexture(std::string path);

private:
	SDL_Window* window;
	SDL_Renderer* renderer = nullptr;
	SDL_Event event;
};
