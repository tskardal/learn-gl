#include "window.h"

namespace LearnGL
{
    class SDLWindow : public Window
    {
    public:
	SDLWindow();
	virtual ~SDLWindow();
    private:
	bool initSDL();
	bool initGL();
    };
};

using namespace LearnGL;

SDLWindow::SDLWindow()
{
    printf("Creating SDL window\n");
}

SDLWindow::~SDLWindow()
{
    printf("Deleting SDL window\n");
}

bool SDLWindow::initSDL()
{
    return false;
}

bool SDLWindow::initGL()
{
    return false;
}
