#include <cstdio>

namespace LearnGL
{
    class Window
    {
    protected:
	int m_width;
	int m_height;
	int m_bpp;
	bool m_fullscreen;
	
    public:
	Window();
	virtual ~Window();
	
	void create(int width, int height, int bpp, bool fullscreen);
	void nextFrame();
	bool isFullscreen();
    };
};


using namespace LearnGL;

Window::Window()
{

}

Window::~Window()
{
        printf("Deleting base class window\n");
}

void Window::create(int width, int height, int bpp, bool fullscreen)
{
    m_width = width;
    m_height = height;
    m_bpp = bpp;
    m_fullscreen = fullscreen;
}

bool Window::isFullscreen(){
    return m_fullscreen;
}


void Window::nextFrame()
{
    // next frame please
}
