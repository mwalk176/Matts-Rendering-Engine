#ifndef MRAYTRACER_H
#define MRAYTRACER_H

#include "Integrator.h"
#include "../Materials/MRayTracerMat.h"
#include "../Scene/Lights/DirectionalLight.h"
#include "../Scene/Lights/PointLight.h"
#include "RenderSettings.h"



class MRayTracer : public Integrator {
public:
	Vec3 render(Ray camRay, Scene& scene);

private:
	Vec3 trace(Ray ray, Scene& scene, int depth);
	Material* getMaterial(std::vector<Material*> materials);
	RenderSettings* settings = RenderSettings::getInstance();
};



#endif
