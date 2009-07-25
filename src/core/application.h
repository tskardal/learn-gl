#ifndef APPLICATION_H
#define APPLICATION_H

namespace LearnGL
{
    class Application
    {
    public:
	Application(){}
	virtual ~Application(){ }

	virtual void init() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
    };
};

#endif
