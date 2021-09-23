#ifndef MPATHTRACER_H
#define MPATHTRACER_H

#define _USE_MATH_DEFINES

#include "Integrator.h"
#include "../Scene/Lights/DirectionalLight.h"
#include "../Scene/Lights/PointLight.h"
#include "../Materials/MPathTracerMat.h"

#include <chrono>


class MPathTracer : public Integrator {
public:
	Vec3 render(Ray camRay, Scene& scene);

private:
	Vec3 trace(Ray ray, Scene& scene, int depth, bool calculateEmission);
	Vec3 computeRandomReflection(Vec3 alignedNormal);
	Vec3 computeShadowRay(Vec3 normalOrigin, Vec3 intersectionPoint, Scene& scene, 
		Vec3 alignedNormal, Vec3 objectColor, Vec3 normal);

	//Material* getMaterial(std::vector<Material*> materials);
	//RenderSettings* settings = RenderSettings::getInstance();

};






#endif
