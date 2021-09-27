#ifndef MDEBUG_H
#define MDEBUG_H

#define _USE_MATH_DEFINES

#include "Integrator.h"


class MDebug : public Integrator {
public:
	MDebug();
	MDebug(Scene* s);
	Vec3 render(Ray camRay);

private:


};



#endif
