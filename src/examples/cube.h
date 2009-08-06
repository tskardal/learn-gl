#ifndef EXAMPLE_CUBE_H
#define EXAMPLE_CUBE_H

#include <vector>
#include "../core/application.h"

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

class CubeExample : public LearnGL::Application
{
public:
    CubeExample();
    virtual ~CubeExample(){ }

    void init();
    void draw();
    void update();

private:
    vector<Vertex> m_vertices;
    vector<Vertex> m_colors;
    float m_angle;
};

#endif

CubeExample::CubeExample()
{
    m_angle = 0.0f;
    init();
}

void CubeExample::init()
{
    glShadeModel(GL_SMOOTH);		// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	// Black Background
    glClearDepth(1.0f);			// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do


    // setup cube
    m_vertices.push_back(Vertex(-1.0f, -1.0f,  1.0f ));//Vertex
    m_colors.push_back(Vertex(1.0, 0.0, 0.0));//Color
    m_vertices.push_back(Vertex( 1.0f, -1.0f,  1.0f ));
    m_colors.push_back(Vertex(1.0, 0.0, 0.0));
    m_vertices.push_back(Vertex( 1.0f,  1.0f,  1.0f ));
    m_colors.push_back(Vertex(1.0, 0.0, 0.0));
    m_vertices.push_back(Vertex(-1.0f,  1.0f,  1.0f ));
    m_colors.push_back(Vertex(1.0, 0.0, 0.0));
    
    m_vertices.push_back(Vertex(-1.0f, -1.0f, -1.0f ));
    m_colors.push_back(Vertex(1.0, 1.0, 0.0));
    m_vertices.push_back(Vertex(-1.0f,  1.0f, -1.0f ));
    m_colors.push_back(Vertex(1.0, 1.0, 0.0));
    m_vertices.push_back(Vertex( 1.0f,  1.0f, -1.0f ));
    m_colors.push_back(Vertex(1.0, 1.0, 0.0));
    m_vertices.push_back(Vertex( 1.0f, -1.0f, -1.0f ));
    m_colors.push_back(Vertex(1.0, 1.0, 0.0));
    
    m_vertices.push_back(Vertex(-1.0f,  1.0f, -1.0f ));
    m_colors.push_back(Vertex(1.0, 1.0, 1.0));
    m_vertices.push_back(Vertex(-1.0f,  1.0f,  1.0f ));
    m_colors.push_back(Vertex(1.0, 1.0, 1.0));
    m_vertices.push_back(Vertex( 1.0f,  1.0f,  1.0f ));
    m_colors.push_back(Vertex(1.0, 1.0, 1.0));
    m_vertices.push_back(Vertex( 1.0f,  1.0f, -1.0f ));
    m_colors.push_back(Vertex(1.0, 1.0, 1.0));
    
    m_vertices.push_back(Vertex(-1.0f, -1.0f, -1.0f ));
    m_colors.push_back(Vertex(0.0, 1.0, 1.0));
    m_vertices.push_back(Vertex( 1.0f, -1.0f, -1.0f ));
    m_colors.push_back(Vertex(0.0, 1.0, 1.0));
    m_vertices.push_back(Vertex( 1.0f, -1.0f,  1.0f ));
    m_colors.push_back(Vertex(0.0, 1.0, 1.0));
    m_vertices.push_back(Vertex(-1.0f, -1.0f,  1.0f ));
    m_colors.push_back(Vertex(0.0, 1.0, 1.0));
    
    m_vertices.push_back(Vertex( 1.0f, -1.0f, -1.0f ));
    m_colors.push_back(Vertex(0.0, 1.0, 0.0));
    m_vertices.push_back(Vertex( 1.0f,  1.0f, -1.0f ));
    m_colors.push_back(Vertex(0.0, 1.0, 0.0));
    m_vertices.push_back(Vertex( 1.0f,  1.0f,  1.0f ));
    m_colors.push_back(Vertex(0.0, 1.0, 0.0));
    m_vertices.push_back(Vertex( 1.0f, -1.0f,  1.0f ));
    m_colors.push_back(Vertex(0.0, 1.0, 0.0));
    
    m_vertices.push_back(Vertex(-1.0f, -1.0f, -1.0f ));
    m_colors.push_back(Vertex(0.0, 0.0, 1.0));
    m_vertices.push_back(Vertex(-1.0f, -1.0f,  1.0f ));
    m_colors.push_back(Vertex(0.0, 0.0, 1.0));
    m_vertices.push_back(Vertex(-1.0f,  1.0f,  1.0f ));
    m_colors.push_back(Vertex(0.0, 0.0, 1.0));
    m_vertices.push_back(Vertex(-1.0f,  1.0f, -1.0f ));
    m_colors.push_back(Vertex(0.0, 0.0, 1.0));
}

void CubeExample::update()
{
    m_angle += 0.03f;

    if(m_angle > 360)
	m_angle = 0.0f;
}

void CubeExample::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -8.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &m_vertices[0]);
    glColorPointer(3, GL_FLOAT, 0, &m_colors[0]);

    glRotatef(m_angle, 0.2, 0.4, 0.6);

    glDrawArrays(GL_QUADS, 0, m_vertices.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);   
}
