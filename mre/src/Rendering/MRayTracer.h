#ifndef MRAYTRACER_H
#define MRAYTRACER_H

#include "Integrator.h"


class MRayTracer : public Integrator {
public:
	Vec3 render(Ray camRay, Scene& scene);

private:

};



#endif
