#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "../Utils/Vec3.h"
#include "../Utils/Ray.h"
#include "../Scene/Scene.h"


class Integrator {
public:
	virtual Vec3 render(Ray camRay, Scene& scene) = 0;

private:

};




#endif
