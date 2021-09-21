#ifndef SPHERE_H
#define SPHERE_H

#include "SceneObject.h"
#include "../../Materials/Material.h"


class Sphere : public SceneObject {
public:
	Sphere();
	Sphere(Vec3 p);
	Sphere(Vec3 p, double r);
	Sphere(Vec3 p, double r, Material* mat);
	Sphere(Vec3 p, double r, std::vector<Material*> mats);

	Vec3 getPos();
	bool intersect(Ray r, double& p0, double& p1);
	Vec3 computeNormal(Vec3 intersectionPoint);
	Vec3 getNewDirectionTowardsLight(Vec3 shadowRay, Vec3 alignedNormal, Vec3 normalFromLight, double& angleToObject, Vec3 intersectionPoint);
	double getRadius();

	std::string toString();
	//friend std::ostream& operator<<(std::ostream& os, SceneObject const& s);


private:
	double radius;

};

#endif