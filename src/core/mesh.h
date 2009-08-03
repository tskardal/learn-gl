#ifndef MESH_H
#define MESH_H

#include <string>

using namespace std;

namespace LearnGL
{
    class Mesh
    {
    public:
        Mesh(const string& filename) : m_filename(filename) { }
	virtual ~Mesh() {};
	virtual void draw() = 0;

    protected:
	virtual void load() = 0;       

	string m_filename;
    };
};

#endif
