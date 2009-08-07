#ifndef OBJMESH_H
#define OBJMESH_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include "vector2.h"
#include "vector3.h"
#include "mesh.h"
#include "ObjMaterial.h"

namespace LearnGL
{
    class ObjMesh : public LearnGL::Mesh
    {
    public:
        ObjMesh(const string& filename) : Mesh(filename) { load(); }
	virtual ~ObjMesh();
	virtual void draw();

    protected:
	void load();

    private:
	vector<Vector3> m_vertices;
	vector<Vector2> m_texcoords;
	vector<Vector3> m_normals;
	vector<Vector3> m_colors;

	void addVector3(vector<string> tokens, vector<Vector3>* target);
	void addVector2(vector<string> tokens, vector<Vector2>* target);
	void addFace(vector<string> tokens, vector<Face>* target);
	void generateArrays(vector<Vector3>, vector<Vector2>,
			    vector<Vector3>, vector<Face>);
    };
};

#endif

ObjMesh::~ObjMesh()
{
}

void ObjMesh::load()
{
    // temporary storage
    vector<Vector3> vertices;
    vector<Vector2> texcoords;
    vector<Vector3> normals;
    vector<Face> faces;
    


    ifstream in(m_filename.c_str());
    string line;

    cout << "start parsing " << m_filename << endl;

    while(getline(in, line))
    {
	istringstream iss(line);
        vector<string> tokens;

	// extract tokens and copy to a vector
	copy(istream_iterator<string>(iss),
	     istream_iterator<string>(),
	     back_inserter<vector<string> >(tokens));	

	if(tokens.size() == 0) 
	    continue;

	string type = tokens[0];

	if(type == "v")  // vertex
	{
	    addVector3(tokens, &vertices);
	}
	if(type == "vt") // texture vertex
	{
	    addVector2(tokens, &texcoords);
	}
	if(type == "vn") // normal vertex
	{
	    addVector3(tokens, &normals);
	}

	if(type == "f")  // face
	{
	    addFace(tokens, &faces);
	}

	if(type == "mtllib") // material definition
	{
	    ObjMaterial mtl(tokens[1]);
	}

	if(type == "usemtl") // material activation
	{
	}
    }

    generateArrays(vertices, texcoords, normals, faces);
}

void ObjMesh::generateArrays(vector<Vector3> vertices, 
			     vector<Vector2> texcoords,
			     vector<Vector3> normals,
			     vector<Face> faces)
{
    cout << "starting array creation" << endl;
    vector<Face>::iterator it;

    for(it = faces.begin(); it != faces.end(); ++it)
    {
	Face f = *it;	
	int count = f.Vertices.size();

	// get vertex defined by a index at face.Vertices[i]
	// -1 because vertices starts at 0, while faces start at 1
	for(int i = 0; i < count; i++)
	{	   	    
	    if(f.Vertices.size() > 0)
		m_vertices.push_back(vertices[f.Vertices[i]-1]);

	    if(f.TextureVertices.size() > 0)
		m_texcoords.push_back(texcoords[f.TextureVertices[i-1]]);

	    if(f.NormalVertices.size() > 0)
		m_normals.push_back(normals[f.NormalVertices[i-1]]);
	   
	    //m_colors.push_back(Vector3(0.0, 1.0, 0.0));
	}
    }

    cout << "ending array creation" << endl;
    cout << "v: " << m_vertices.size() << endl;
    cout << "vt: " << m_texcoords.size() << endl;
    cout << "vn: " << m_normals.size() << endl;
}

void ObjMesh::draw()
{          
    glPushMatrix();

    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glVertexPointer(3, GL_FLOAT, 0, &m_vertices[0]);
//    glColorPointer(3, GL_FLOAT, 0, &m_colors[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &m_texcoords[0]);
    
    glDrawArrays(GL_POLYGON, 0, m_vertices.size());

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_COLOR_ARRAY);

    glPopMatrix();
}

void ObjMesh::addVector2(vector<string> src, vector<Vector2>* dest)
{
    float x, y;

    stringstream xVal(src[1]);
    stringstream yVal(src[2]);
	    
    xVal >> x;
    yVal >> y;

    dest->push_back(Vector2(x, y));
}

void ObjMesh::addVector3(vector<string> src, vector<Vector3>* dest)
{
    float x, y, z;

    stringstream xVal(src[1]);
    stringstream yVal(src[2]);
    stringstream zVal(src[3]);
	    
    xVal >> x;
    yVal >> y;
    zVal >> z;

    dest->push_back(Vector3(x, y, z));
}

void ObjMesh::addFace(vector<string> src, vector<Face>* dest)
{
    Face f;         

    for(vector<string>::iterator it = src.begin(); it != src.end(); ++it)
    {
	// skip 'f'
	if(it == src.begin())
	    continue;

	stringstream iss(*it);
	int i = 0;
	
	for(string each; getline(iss, each, '/');)
	{
	
	    stringstream current(each);
	    int index;      

	    if(each == "")
	    {
		i++;
		continue;
	    }
	    
	    current >> index;
	    
	    switch(i)
	    {
	    case 0:
		f.Vertices.push_back(index);
		break;
	    case 1:
		f.TextureVertices.push_back(index);
		break;
	    case 2:
		f.NormalVertices.push_back(index);
		break;
	    }
	    i++;
	}
    }

    dest->push_back(f);
}
