
#include <iostream>
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

SDL_Window* g_sdl_window = nullptr;
SDL_Renderer* g_sdl_renderer = nullptr;
bool g_shouldExit = false;

void Render()
{
	SDL_SetRenderDrawColor(g_sdl_renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(g_sdl_renderer);
	SDL_RenderPresent(g_sdl_renderer);
}

void GameLoop()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT: g_shouldExit = true; break;
		}
	}

	Render();
}

int main(int argc, char** argv)
{
	SDL_Init(SDL_INIT_VIDEO);
	g_sdl_window = SDL_CreateWindow("Hello SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	g_sdl_renderer = SDL_CreateRenderer(g_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(GameLoop, 0, 1);
#else
	while (!g_shouldExit)
		GameLoop();
#endif
	
	SDL_DestroyRenderer(g_sdl_renderer);
	SDL_DestroyWindow(g_sdl_window);
	SDL_Quit();

	return 0;
}