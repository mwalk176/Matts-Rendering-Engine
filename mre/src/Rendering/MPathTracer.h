#ifndef MPATHTRACER_H
#define MPATHTRACER_H

#define _USE_MATH_DEFINES

#include "Integrator.h"
#include "../Scene/Lights/DirectionalLight.h"
#include "../Scene/Lights/PointLight.h"
#include "../Materials/MPathTracerMat.h"


class MPathTracer : public Integrator {
public:
	Vec3 render(Ray camRay, Scene& scene);

private:
	Vec3 trace(Ray ray, Scene& scene, int depth, bool calculateEmission);
	//Material* getMaterial(std::vector<Material*> materials);
	//RenderSettings* settings = RenderSettings::getInstance();

};






#endif
