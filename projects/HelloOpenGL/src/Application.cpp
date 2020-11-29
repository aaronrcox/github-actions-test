#include "Application.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

struct EmscriptenGameLoopFunc
{
	static void Execute() { app->GameLoop(); }
	static Application* app;
};
Application* EmscriptenGameLoopFunc::app = nullptr;

#endif

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>


Application::Application()
{

}

Application::~Application()
{

}

void Application::Run()
{
	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow(m_windowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		m_windowWidth, m_windowHeight, SDL_WINDOW_OPENGL);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetSwapInterval(0);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_GLContext glContext = SDL_GL_CreateContext(m_window);

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			
	// Initialise glew
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();

	
	// Now that our window and opengl context is created
	Load();

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

	Unload();

	// clearnup
	SDL_GL_DeleteContext(glContext);
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

	// end of frame, swap the opengl back bufer
	SDL_GL_SwapWindow(m_window);
}

void Application::Load()
{

}

void Application::Unload()
{

}

void Application::Update()
{

}

void Application::Render()
{

}