#include <iostream>

#include "core/SDLwindow.h"

using namespace LearnGL;

int main(int argc, char** argv)
{
    Window* wnd = new SDLWindow();

    delete wnd;

    std::cout << "lala :)" << std::endl;
}
