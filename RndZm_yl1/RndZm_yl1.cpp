#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "RndZm_yl1.h"


using namespace std;
void cleanup(SDL_Window* win);

int main(int argc, char *argv[])
{
	
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		return 1;
		
	}
	
	//Creation de la fenetre

	int width = 1280;
	int height = 720;
	SDL_Window* win = SDL_CreateWindow("RndZm", width, height, 0);
	
	if (!win) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		cleanup(win);
		return 1;

	}

	//Creation du main game loop
	bool running = true;
	while (running) 
	{
		
		SDL_Event event{ 0 };
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
				case SDL_EVENT_QUIT:
					{
						running = false;
						break;
					}
{}
			}
		
		}
	
	}

	cleanup(win);
	return 0;
}

void cleanup(SDL_Window* win) {
	SDL_DestroyWindow(win);
	SDL_Quit();

}
