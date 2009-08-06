#ifndef OBJMATERIAL_H
#define OBJMATERIAL_H

#include <string>
#include <vector>

#include "vector3.h"

using std::string;

namespace LearnGL
{
    class ObjMaterial
    {
    public:
	ObjMaterial(const string& filename) { }
	~ObjMaterial() { }
    };

    struct Face
    {
	vector<int> Vertices;
	vector<int> TextureVertices;
	vector<int> NormalVertices;
    };
};

#endif
