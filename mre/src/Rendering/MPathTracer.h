#ifndef MPATHTRACER_H
#define MPATHTRACER_H

#define _USE_MATH_DEFINES

#include "Integrator.h"
#include "../Scene/Lights/DirectionalLight.h"
#include "../Scene/Lights/PointLight.h"
#include "../Materials/MPathTracerMat.h"

#include <chrono>
#include <vector>


class MPathTracer : public Integrator {
public:
	MPathTracer();
	MPathTracer(Scene* s);
	Vec3 render(Ray camRay);
	

private:
	Vec3 trace(Ray ray, int depth, bool calculateEmission);
	Vec3 computeRandomReflection(Vec3 alignedNormal);
	Vec3 computeShadowRay(Vec3 normalOrigin, Vec3 intersectionPoint, 
		Vec3 alignedNormal, Vec3 objectColor, Vec3 normal);
	Vec3 jitterRay(Vec3 n, Vec3 d, float roughness);

	//Material* getMaterial(std::vector<Material*> materials);
	//RenderSettings* settings = RenderSettings::getInstance();

	//Scene scene;
	Vec3 backgroundColor;
	std::vector<SceneObject*> objects; //remove these later
	std::vector<Light*> lights; //todo remove this later

};






#endif
