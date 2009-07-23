#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <cstdio>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

using namespace std;

namespace LearnGL
{
    class Window
    {
    protected:
	int m_width;
	int m_height;
	int m_bpp;
	bool m_fullscreen;
	bool m_running;
	string m_title;
    public:
	Window();
	virtual ~Window();
	
	virtual void create(int width, int height, int bpp, bool fullscreen, const string& title) = 0;
	virtual void nextFrame() = 0;
	virtual bool isFullscreen();
	virtual bool isRunning();
    };
};

#endif

using namespace LearnGL;

Window::Window(){}

Window::~Window(){}

bool Window::isFullscreen()
{
    return m_fullscreen;
}

bool Window::isRunning()
{
    return m_running;
}
