#ifndef VECTOR2_H
#define VECTOR2_H

namespace LearnGL
{
    template<class T>
    class Vector2t
    {
    public:
	Vector2t(T xVal, T yVal) 
	    : x(xVal), y(yVal) {}

	T x;
	T y;
    };

    typedef Vector2t<float> Vector2; // suppose floats are most common
};

#endif
