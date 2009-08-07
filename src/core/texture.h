#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include "GL/gl.h"
#include "IL/il.h"

using std::string;

namespace LearnGL
{
    class Texture
    {
    public:
	Texture(const string& filename);
	~Texture();      
	void enable();

    private:
	void init(const string& filename);	
	GLuint m_image;
    };
};

#endif

Texture::Texture(const string& filename)
{
    ilInit();
    init(filename);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_image);
}

void Texture::init(const string& filename)
{
    ILuint tempImg;

    ilGenImages(1, &tempImg);
    ilBindImage(tempImg);

    ILboolean success = ilLoadImage(filename.c_str());
    if(success)
    {
	success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	    
	if(!success)
	{
	    // TODO: throw exception
	    SDL_Quit();
	}
	else
	{
	    glEnable(GL_TEXTURE_2D);
	    glGenTextures(1, &m_image);
	    glBindTexture(GL_TEXTURE_2D, m_image);
	    glTexParameteri(GL_TEXTURE_2D, 
			    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, 
			    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), 
			 ilGetInteger(IL_IMAGE_WIDTH),
			 ilGetInteger(IL_IMAGE_HEIGHT), 0, 
			 ilGetInteger(IL_IMAGE_FORMAT), 
			 GL_UNSIGNED_BYTE, ilGetData());

	    std::cout << "Texture loaded" << std::endl;	    
	}
    }
    else
    {
	// TODO: throw exception
    }
    
    ilDeleteImages(1, &tempImg);
}

void Texture::enable()
{
    glBindTexture(GL_TEXTURE_2D, m_image);
}
