#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "RndZm_yl1.h"
#include "SDL3_image/SDL_image.h"
#include <cmath>



using namespace std;
struct SDLState
{
	SDL_Window *window;
	SDL_Renderer* renderer;
	int width, height, logW, logH;
};


bool initialize(SDLState& state);
void cleanup(SDLState& state);
SDL_FPoint GetMouseLogical(const SDLState& state);

int main(int argc, char *argv[])
{
	SDLState state;
	state.width = 1280;
	state.height = 720;
	state.logW = 640;
	state.logH = 320;

	constexpr float PLAYER_SIZE = 32.0f;
	constexpr float PLAYER_HALF = PLAYER_SIZE * 0.5f;

	if (!initialize(state)) {
		return 1;
	}

	//loading game assets
	SDL_Texture* idleTex = IMG_LoadTexture(state.renderer, "assets/playerAnimation/idle.png");
	SDL_SetTextureScaleMode(idleTex, SDL_SCALEMODE_NEAREST);


	//setup game data

	//Keyboard movement
	const bool *keys = SDL_GetKeyboardState(nullptr);
	float playerX = 0.0f;
	float playerY = 0.0f;
	const float playerSpeed = 150.0f;

	//mouse input
	float playerAngle = 0.0f;


	//tick
	Uint64 lastTicks = SDL_GetTicks();


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
				case SDL_EVENT_WINDOW_RESIZED:
					{
						state.width = event.window.data1;
						state.height = event.window.data2;
						break;
					}
			}
		
		}
		//Timing ticks
		Uint64 currentTicks = SDL_GetTicks();
		float deltaTime = (currentTicks - lastTicks) / 1000.0f;
		lastTicks = currentTicks;

		//Input movement keys
		if (keys[SDL_SCANCODE_A]) playerX -= playerSpeed * deltaTime;
		if (keys[SDL_SCANCODE_D]) playerX += playerSpeed * deltaTime;
		if (keys[SDL_SCANCODE_W]) playerY -= playerSpeed * deltaTime;
		if (keys[SDL_SCANCODE_S]) playerY += playerSpeed * deltaTime;

		//Input movement mouse
		SDL_FPoint mouse = GetMouseLogical(state);



		float dx = mouse.x - (playerX + PLAYER_HALF);
		float dy = mouse.y - (playerY + PLAYER_HALF);


		playerAngle = atan2f(dy, dx) * 180.0f / SDL_PI_F + 90.0f;




	
		//Drawing
		
		SDL_SetRenderDrawColor(state.renderer, 20, 10, 30, 255);
		SDL_RenderClear(state.renderer);
		
		SDL_FRect src{
			.x = 0,
			.y = 0,
			.w = 32,
			.h = 32
		};


		SDL_FRect dst{
			.x = playerX,
			.y = playerY,
			.w = 32,
			.h = 32
		};


		SDL_RenderTextureRotated(
			state.renderer,
			idleTex,
			&src,
			&dst,
			playerAngle,
			nullptr,
			SDL_FLIP_NONE
		);



		//flip backbufer to front
		SDL_RenderPresent(state.renderer);

	}

	SDL_DestroyTexture(idleTex);
	cleanup(state);
	return 0;
}

bool initialize(SDLState& state) {
	
	bool initSuccess = true;
	if (!SDL_Init(SDL_INIT_VIDEO)) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		initSuccess = false;

	}

	//Window base settings
	state.window = SDL_CreateWindow("RndZm", state.width, state.height, SDL_WINDOW_RESIZABLE);

	if (!state.window) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", nullptr);
		cleanup(state);
		initSuccess = false;

	}

	//Renderer
	state.renderer = SDL_CreateRenderer(state.window, nullptr);
	if (!state.renderer) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Error initializing SDL3", state.window);
		cleanup(state);
		initSuccess = false;

	}


	//conf presentation
	SDL_SetRenderLogicalPresentation(state.renderer, state.logW, state.logH, SDL_LOGICAL_PRESENTATION_LETTERBOX);

	return initSuccess;
}

void cleanup(SDLState &state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();

}
SDL_FPoint GetMouseLogical(const SDLState& state)
{
	float x, y;
	SDL_GetMouseState(&x, &y);

	x *= (float)state.logW / state.width;
	y *= (float)state.logH / state.height;

	return { x, y };
}
