#include "window.h"

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
    // todo: remove this (it's duplicate)
    m_width = width;
    m_height = height;
    m_bpp = bpp;
    m_fullscreen = fullscreen;
    m_title = title;

    printf("hmmm\n");
    if(!initSDL())
    {
	printf("Error\n");
    }
    else
    {
	m_running = true;
	printf("Yay\n");
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
    
    // window caption
    SDL_WM_SetCaption(m_title.c_str(), NULL);

    return true;
}

bool SDLWindow::initGL()
{
    // black background color
    glClearColor(0, 0, 0, 0);

    // projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    return true;
}

void SDLWindow::nextFrame()
{
    SDL_GL_SwapBuffers();
}
