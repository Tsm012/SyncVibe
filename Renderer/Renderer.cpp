/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

/* Headers */
//Using SDL and STL string
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>

/* Constants */
//Screen dimension constants
constexpr int kScreenWidth{ 640 };
constexpr int kScreenHeight{ 480 };

/* Function Prototypes */
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

/* Global Variables */
//The window we'll be rendering to
SDL_Window* gWindow{ nullptr };

//The surface contained by the window
SDL_Surface* gScreenSurface{ nullptr };

/* Function Implementations */
bool init()
{
	//Initialization flag
	bool success{ true };

	//Initialize SDL
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create window
		if (gWindow = SDL_CreateWindow("SDL3 Tutorial: Render a Square", kScreenWidth, kScreenHeight, 0); gWindow == nullptr)
		{
			SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	gScreenSurface = nullptr;

	//Quit SDL subsystems
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Final exit code
	int exitCode{ 0 };

	//Initialize
	if (!init())
	{
		SDL_Log("Unable to initialize program!\n");
		exitCode = 1;
	}
	else
	{
		//The quit flag
		bool quit{ false };

		//The event data
		SDL_Event e;
		SDL_zero(e);

		//The main loop
		while (quit == false)
		{
			//Get event data
			while (SDL_PollEvent(&e))
			{
				//If event is quit type
				if (e.type == SDL_EVENT_QUIT)
				{
					//End the main loop
					quit = true;
				}
			}

			//Fill the surface white
			SDL_FillSurfaceRect(gScreenSurface, nullptr, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0xFF, 0xFF));

			//Define a red square
			SDL_Rect fillRect = { (kScreenWidth - 200) / 2, (kScreenHeight - 200) / 2, 200, 200 };
			SDL_FillSurfaceRect(gScreenSurface, &fillRect, SDL_MapSurfaceRGB(gScreenSurface, 0xFF, 0x00, 0x00));

			//Update the surface
			SDL_UpdateWindowSurface(gWindow);
		}
	}

	//Clean up
	close();

	return exitCode;
}
