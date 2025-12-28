#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "RndZm_yl1.h"


using namespace std;
struct SDLState
{
	SDL_Window *window;
	SDL_Renderer* renderer;
};



void cleanup(SDLState& state);

int main(int argc, char *argv[])
{
	SDLState state;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		return 1;
		
	}
	
	//Window base settings

	int width = 1280;
	int height = 720;
	state.window = SDL_CreateWindow("RndZm", width, height, 0);
	
	if (!state.window) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		cleanup(state);
		return 1;

	}

	//Renderer
	state.renderer = SDL_CreateRenderer(state.window, nullptr);
	if (!state.renderer) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", state.window);
		cleanup(state);
		return 1;

	}


	//Main game loop

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
	
		//Drawing
		
		SDL_SetRenderDrawColor(state.renderer, 0, 255, 0, 255);
		SDL_RenderClear(state.renderer);

		//flip backbufer to front
		SDL_RenderPresent(state.renderer);

	}

	cleanup(state);
	return 0;
}

void cleanup(SDLState &state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();

}
