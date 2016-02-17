#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:

	bool isClosed;
	int FPS;

	Display(int width, int height, const std::string& title);
	void Update();
	bool IsClosed()
	{
		return isClosed;
	}

	virtual ~Display();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
};

#endif