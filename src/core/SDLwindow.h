#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include "window.h"
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

using namespace std;

namespace LearnGL
{
    class SDLWindow : public Window
    {
    public:
	SDLWindow();
	virtual ~SDLWindow();
	void create(int width, int height, int bpp, bool fullscreen, const string& title);
	void nextFrame();
	void resize(int x, int y);
    private:
	bool initSDL();
	bool initGL(); // perhaps unnecessary, or should be virtual
    };
};

using namespace LearnGL;

SDLWindow::SDLWindow()
{
    m_running = false;
    printf("Creating SDL window\n");
}

SDLWindow::~SDLWindow()
{
    printf("Deleting SDL window\n");
}

void SDLWindow::create(int width, int height, int bpp, bool fullscreen, const string& title)
{
    // todo: this don't feel right. should be handled by class Window
    m_width = width;
    m_height = height;
    m_bpp = bpp;
    m_fullscreen = fullscreen;
    m_title = title;

    if(!initSDL())
    {
	printf("Error creating SDL window.\n");
	// later, throw exception
    }
    else
    {
	m_running = true;
    }
}

bool SDLWindow::initSDL()
{
    printf("init..\n");

    // initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
	return false;
    }

    // create a window
    if(SDL_SetVideoMode(m_width, m_height, m_bpp, SDL_OPENGL) == NULL)
    {
	return false;
    }

    // tutorial says "at least"? todo: find out why and what!
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    // window caption
    SDL_WM_SetCaption(m_title.c_str(), NULL);

    // force resize event needed by ogl
    SDL_Event resizeEvent;
    resizeEvent.type=SDL_VIDEORESIZE;
    resizeEvent.resize.w=m_width;
    resizeEvent.resize.h=m_height;
    SDL_PushEvent(&resizeEvent);    

    return true;
}

void SDLWindow::resize(int x, int y)
{
    if(y <= 0)
	y = 1;

    glViewport(0, 0, x, y);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)x / (GLfloat)y, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SDLWindow::nextFrame()
{
    SDL_GL_SwapBuffers();
}

#endif
