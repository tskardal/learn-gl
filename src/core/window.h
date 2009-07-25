#ifndef WINDOW_H
#define WINDOW_H

#include <cstdio>
#include <string>

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
	Window(){ }
	virtual ~Window(){ }
	
	virtual void create(int width, int height, int bpp, bool fullscreen, const string& title) = 0;
	virtual void nextFrame() = 0;
	virtual void resize(int x, int y) = 0;
	virtual bool isFullscreen(){ return m_fullscreen; }
	virtual bool isRunning(){ return m_running; }
    };
};

#endif
