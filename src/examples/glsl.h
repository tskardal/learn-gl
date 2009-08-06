#ifndef EXAMPLE_GLSL_H
#define EXAMPLE_GLSL_H

#include "../core/application.h"
#include "../core/ObjMesh.h"

using namespace LearnGL;

class GLSLExample : public LearnGL::Application
{
public:
    GLSLExample();
    virtual ~GLSLExample();
    
    void init();
    void draw();
    void update();

private:
    void setShaders();
    char* readTextFile(string filename);

    Mesh* m_mesh;
    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    GLuint m_shaderProgram;
};

#endif

GLSLExample::GLSLExample()
{
    init();
}

GLSLExample::~GLSLExample()
{
    delete m_mesh;
}

void GLSLExample::init()
{
    glewInit();

    if(glewIsSupported("GL_VERSION_2_1"))
	printf("Ready for OpenGL 2.1\n");
    else if(glewIsSupported("GL_VERSION_2_0"))
	printf("Ready for OpenGL 2.0\n");
    else
    {
	printf("OpenGL 2.x not supported\n");
	SDL_Quit();
    }

    setShaders();

    m_mesh = new ObjMesh("examples/sample.obj");
}

void GLSLExample::draw()
{
    m_mesh->draw();
}

void GLSLExample::update()
{
}

void GLSLExample::setShaders()
{
    char *fs, *vs;

    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    fs = readTextFile("examples/sample.vert");
    vs = readTextFile("examples/sample.frag");

    const char* ff = fs;
    const char* vv = vs;

    glShaderSource(m_vertexShader, 1, &vv, NULL);
    glShaderSource(m_fragmentShader, 1, &ff, NULL);

    free(vs);
    free(fs);

    glCompileShader(m_vertexShader);
    glCompileShader(m_fragmentShader);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glAttachShader(m_shaderProgram, m_vertexShader);

    glLinkProgram(m_shaderProgram);
    glUseProgram(m_shaderProgram);
}

char* GLSLExample::readTextFile(string filename)
{
    FILE *fp;
    char *content = NULL;
    
    int count=0;
    
    if (filename.c_str() != NULL) {
	fp = fopen(filename.c_str(),"rt");
	
	if (fp != NULL) {
	    
	    fseek(fp, 0, SEEK_END);
	    count = ftell(fp);
	    rewind(fp);
	    
	    if (count > 0) {
		content = (char *)malloc(sizeof(char) * (count+1));
		count = fread(content,sizeof(char),count,fp);
		content[count] = '\0';
	    }
	    fclose(fp);
	}
    }

    return content;
}
