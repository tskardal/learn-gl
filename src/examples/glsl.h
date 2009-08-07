#ifndef EXAMPLE_GLSL_H
#define EXAMPLE_GLSL_H

#include <GL/glew.h>

#include "../core/application.h"
#include "../core/ObjMesh.h"
#include "../core/texture.h"

void printShaderInfoLog(GLuint);
void printProgramInfoLog(GLuint);


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
    Texture* m_texture;
    float m_angle;
    GLuint m_vertexShader;
    GLuint m_fragmentShader;
    GLuint m_shaderProgram;
};

#endif

GLSLExample::GLSLExample()
{
    init();
    m_angle = 0.0f;
}

GLSLExample::~GLSLExample()
{
    delete m_texture;
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

    m_mesh = new ObjMesh("examples/l3dx.obj");

    glShadeModel(GL_SMOOTH);		// Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);	// Black Background
    glClearDepth(1.0f);			// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
    glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do

    cout << "GL_VERSION: " << glGetString(GL_VERSION) << endl;

    m_texture = new Texture("examples/l3dx.png");
}

void GLSLExample::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -8.0f);
    glRotatef(m_angle, 0.2f, 0.6f, 0.5f);

    m_texture->enable();
  
    m_mesh->draw();  
}

void GLSLExample::update()
{
    m_angle += 0.03f;

    if(m_angle > 360)
	m_angle = 0.0f;
}

void GLSLExample::setShaders()
{
    char *fs, *vs;

    m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    fs = readTextFile("examples/sample.frag");
    vs = readTextFile("examples/sample.vert");

    const char* ff = fs;
    const char* vv = vs;

    glShaderSource(m_vertexShader, 1, &vv, NULL);
    glShaderSource(m_fragmentShader, 1, &ff, NULL);

    free(vs);
    free(fs);

    glCompileShader(m_vertexShader);
    glCompileShader(m_fragmentShader);

    printShaderInfoLog(m_vertexShader);
    printShaderInfoLog(m_fragmentShader);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, m_fragmentShader);
    glAttachShader(m_shaderProgram, m_vertexShader);

    glLinkProgram(m_shaderProgram);

    printProgramInfoLog(m_shaderProgram);

    glUseProgram(m_shaderProgram);

    cout << "shader compilation & linking complete" << endl;
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

void printProgramInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}

void printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
        free(infoLog);
    }
}
