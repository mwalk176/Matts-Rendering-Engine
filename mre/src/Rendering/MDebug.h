#ifndef MDEBUG_H
#define MDEBUG_H

#define _USE_MATH_DEFINES

#include "Integrator.h"


class MDebug : public Integrator {
public:
	Vec3 render(Ray camRay, Scene& scene);

private:


};



#endif
