#include "Application.h"
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

struct EmscriptenGameLoopFunc
{
	static void Execute() { app->GameLoop(); }
	static Application* app;
};
Application* EmscriptenGameLoopFunc::app = nullptr;

#endif

Application::Application()
{

}

Application::~Application()
{

}

void Application::Run()
{
	SDL_Init(SDL_INIT_VIDEO);
	m_window = SDL_CreateWindow(m_windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_windowWidth, m_windowHeight, 0);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// load assets
	auto img = SDL_LoadBMP("./HelloSDLAssets/arc-codes.bmp");
	m_image = SDL_CreateTextureFromSurface(m_renderer, img);
	SDL_FreeSurface(img);

	#ifdef __EMSCRIPTEN__
		// The browser requires the main loop to be executed in a callback
		// this way infinite loops do not crash the browser
		EmscriptenGameLoopFunc::app = this;
		emscripten_set_main_loop(EmscriptenGameLoopFunc::Execute, 0, 1);
	#else
		// On windows, we control our own main loop
		// run until the m_quitApplication has been set to true
		while (!m_shouldQuit)
			GameLoop();
	#endif

	// clearnup
	SDL_DestroyTexture(m_image);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Application::GameLoop()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT: m_shouldQuit = true; break;
		}
	}

	Update();
	Render();
}

void Application::Update()
{

}

void Application::Render()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_renderer);

	SDL_Rect rect = { 10, 10, 256, 256 };
	SDL_RenderCopy(m_renderer, m_image, NULL, &rect);

	SDL_RenderPresent(m_renderer);
}