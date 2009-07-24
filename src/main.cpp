#include <iostream>

#include "core/SDLwindow.h"

using namespace LearnGL;

bool processEvents();

int main(int argc, char** argv)
{
    Window* wnd = new SDLWindow();
    wnd->create(800,600,32,false,"Test");

    while(wnd->isRunning()) 
    {
	if(!processEvents())
	{
	    break;

	}
	wnd->nextFrame();
    }

    delete wnd;

    std::cout << "lala :)" << std::endl;
}

// todo: this should be abstracted into its own class
//       perhaps "Application"
bool processEvents()
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
	}
	}
    }
    return true;
}
