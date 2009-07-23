#include <iostream>

#include "core/SDLwindow.h"

using namespace LearnGL;

int main(int argc, char** argv)
{
    Window* wnd = new SDLWindow();
    wnd->create(800,600,32,false,"Test");
    
    while(wnd->isRunning()) 
    {
	wnd->nextFrame();
    }

    delete wnd;

    std::cout << "lala :)" << std::endl;
}
