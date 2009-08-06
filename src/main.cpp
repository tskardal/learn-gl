#define NO_SDL_GLEXT

#include <iostream>
#include <vector>

#include "core/SDLwindow.h"
#include "examples/cube.h"
#include "examples/glsl.h"

using namespace LearnGL;

bool processEvents(Window* wnd);

int main(int argc, char** argv)
{
    Window* wnd = new SDLWindow();
    wnd->create(800,600,32,false,"GLSL baby!");

    Application* app = new GLSLExample();   

    while(wnd->isRunning()) 
    {
	if(!processEvents(wnd))
	{
	    break;
	}
	app->update();
	app->draw();
	wnd->nextFrame();
    }

    delete app;
    delete wnd;

    std::cout << "Shutting down." << std::endl;
}

// todo: this should be abstracted into its own class
//       perhaps "Application"
bool processEvents(Window* wnd)
{
    SDL_Event event;
    
    while(SDL_PollEvent(&event))
    {
	switch(event.type)
	{
	case SDL_QUIT:
	{
	    return false;	    
	}
	case SDL_KEYDOWN:
	{
	    SDLKey sym = event.key.keysym.sym;

	    if(sym == SDLK_ESCAPE)
	    {
		return false;
	    }
	    break;
	}
	case SDL_VIDEORESIZE:
	{
	    wnd->resize(event.resize.w, event.resize.h);
	    break;
	}
	default:
	{
	    break;
	}
	}
    }
    return true;
}
