#ifndef VECTOR3_H
#define VECTOR3_H

namespace LearnGL
{
    template<class T>
    class Vector3t
    {
    public:
	Vector3t(T xVal, T yVal, T zVal)
	    : x(xVal), y(yVal), z(zVal) {}
	T x;
	T y;
	T z;

	// TODO: a lot of operators to overload
    };
    
    typedef Vector3t<float> Vector3; // suppose floats are most common
};

#endif
