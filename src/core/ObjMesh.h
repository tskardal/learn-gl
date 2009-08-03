#ifndef OBJMESH_H
#define OBJMESH_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

#include "vector3.h"
#include "mesh.h"

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
	void addVector3(vector<string> line, vector<Vector3>* target);
    };
};

#endif

ObjMesh::~ObjMesh()
{
}

void ObjMesh::load()
{
    ifstream in(m_filename.c_str());
    string line;

    while(getline(in, line))
    {
	istringstream iss(line);
        vector<string> tokens;

	// extract tokens and copy to a vector
	copy(istream_iterator<string>(iss),
	     istream_iterator<string>(),
	     back_inserter<vector<string> >(tokens));

	if(tokens[0] == "v")
	{
	    addVector3(tokens, &m_vertices);
	}
    }

    cout << "Size: " << m_vertices.size() << endl;
}

void ObjMesh::draw()
{
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
