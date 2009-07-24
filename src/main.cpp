#include <iostream>
#include <vector>

#include "core/SDLwindow.h"

using namespace LearnGL;

bool processEvents(Window* wnd);
void initGL();
void renderCube();

struct Vertex
{
    float x, y, z;

    Vertex(float x, float y, float z)
	{
	    this->x = x;
	    this->y = y;
	    this->z = z;
	}
};

vector<Vertex> vertices;
vector<Vertex> colors;
float angle = 0.0f;

int main(int argc, char** argv)
{
    Window* wnd = new SDLWindow();
    wnd->create(800,600,32,false,"Test");

    initGL();

    while(wnd->isRunning()) 
    {
	if(!processEvents(wnd))
	{
	    break;
	}
	renderCube();
	wnd->nextFrame();
    }

    delete wnd;

    std::cout << "Shutting down." << std::endl;
}

void initGL()
{
    glShadeModel(GL_SMOOTH);		// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	// Black Background
    glClearDepth(1.0f);			// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do


    // setup cube
    vertices.push_back(Vertex(-1.0f, -1.0f,  1.0f ));//Vertex
	colors.push_back(Vertex(1.0, 0.0, 0.0));//Color
	vertices.push_back(Vertex( 1.0f, -1.0f,  1.0f ));
	colors.push_back(Vertex(1.0, 0.0, 0.0));
	vertices.push_back(Vertex( 1.0f,  1.0f,  1.0f ));
	colors.push_back(Vertex(1.0, 0.0, 0.0));
	vertices.push_back(Vertex(-1.0f,  1.0f,  1.0f ));
	colors.push_back(Vertex(1.0, 0.0, 0.0));

	vertices.push_back(Vertex(-1.0f, -1.0f, -1.0f ));
	colors.push_back(Vertex(1.0, 1.0, 0.0));
	vertices.push_back(Vertex(-1.0f,  1.0f, -1.0f ));
	colors.push_back(Vertex(1.0, 1.0, 0.0));
	vertices.push_back(Vertex( 1.0f,  1.0f, -1.0f ));
	colors.push_back(Vertex(1.0, 1.0, 0.0));
	vertices.push_back(Vertex( 1.0f, -1.0f, -1.0f ));
	colors.push_back(Vertex(1.0, 1.0, 0.0));

	vertices.push_back(Vertex(-1.0f,  1.0f, -1.0f ));
	colors.push_back(Vertex(1.0, 1.0, 1.0));
	vertices.push_back(Vertex(-1.0f,  1.0f,  1.0f ));
	colors.push_back(Vertex(1.0, 1.0, 1.0));
	vertices.push_back(Vertex( 1.0f,  1.0f,  1.0f ));
	colors.push_back(Vertex(1.0, 1.0, 1.0));
	vertices.push_back(Vertex( 1.0f,  1.0f, -1.0f ));
	colors.push_back(Vertex(1.0, 1.0, 1.0));

	vertices.push_back(Vertex(-1.0f, -1.0f, -1.0f ));
	colors.push_back(Vertex(0.0, 1.0, 1.0));
	vertices.push_back(Vertex( 1.0f, -1.0f, -1.0f ));
	colors.push_back(Vertex(0.0, 1.0, 1.0));
	vertices.push_back(Vertex( 1.0f, -1.0f,  1.0f ));
	colors.push_back(Vertex(0.0, 1.0, 1.0));
	vertices.push_back(Vertex(-1.0f, -1.0f,  1.0f ));
	colors.push_back(Vertex(0.0, 1.0, 1.0));

	vertices.push_back(Vertex( 1.0f, -1.0f, -1.0f ));
	colors.push_back(Vertex(0.0, 1.0, 0.0));
	vertices.push_back(Vertex( 1.0f,  1.0f, -1.0f ));
	colors.push_back(Vertex(0.0, 1.0, 0.0));
	vertices.push_back(Vertex( 1.0f,  1.0f,  1.0f ));
	colors.push_back(Vertex(0.0, 1.0, 0.0));
	vertices.push_back(Vertex( 1.0f, -1.0f,  1.0f ));
	colors.push_back(Vertex(0.0, 1.0, 0.0));

	vertices.push_back(Vertex(-1.0f, -1.0f, -1.0f ));
	colors.push_back(Vertex(0.0, 0.0, 1.0));
	vertices.push_back(Vertex(-1.0f, -1.0f,  1.0f ));
	colors.push_back(Vertex(0.0, 0.0, 1.0));
	vertices.push_back(Vertex(-1.0f,  1.0f,  1.0f ));
	colors.push_back(Vertex(0.0, 0.0, 1.0));
	vertices.push_back(Vertex(-1.0f,  1.0f, -1.0f ));
	colors.push_back(Vertex(0.0, 0.0, 1.0));
}

void renderCube()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -8.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glColorPointer(3, GL_FLOAT, 0, &colors[0]);

    glRotatef(angle, 0.2, 0.4, 0.6);

    glDrawArrays(GL_QUADS, 0, vertices.size());

    angle += 0.03f;

    if(angle > 360)
	angle = 0.0f;

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);   
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
