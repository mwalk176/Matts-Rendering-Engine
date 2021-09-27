#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "../Utils/Vec3.h"
#include "../Utils/Ray.h"
#include "../Scene/Scene.h"


class Integrator {
public:
	Integrator();
	Integrator(Scene* s);
	virtual Vec3 render(Ray camRay) = 0;
	//virtual void addScene(Scene* scene) = 0;

protected:
	Scene* scene;


private:

};




#endif
