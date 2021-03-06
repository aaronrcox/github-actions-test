#pragma once

// predeclare
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;

class Application
{
public:

	Application();
	virtual ~Application();

	void Run();

	void GameLoop();
	virtual void Load();
	virtual void Unload();
	virtual void Update();
	virtual void Render();

protected:
private:

	const char* m_windowTitle = "Hello World";
	int m_windowWidth = 640;
	int m_windowHeight = 480;

	bool m_shouldQuit = false;

	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_image = nullptr;
};

