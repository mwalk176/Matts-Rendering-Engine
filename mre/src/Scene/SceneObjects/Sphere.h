#ifndef SPHERE_H
#define SPHERE_H

#define SPHERE 0

#include "SceneObject.h"
#include "../../Materials/Material.h"


class Sphere : public SceneObject {
public:
	Sphere();
	Sphere(Vec3 p);
	Sphere(Vec3 p, float r);
	Sphere(Vec3 p, float r, Material* mat);
	Sphere(Vec3 p, float r, std::vector<Material*> mats);

	Vec3 getPos();
	bool intersect(Ray r, float& p0, float& p1);
	Vec3 computeNormal(Vec3 intersectionPoint);
	Vec3 getNewDirectionTowardsLight(Vec3 shadowRay, Vec3 alignedNormal, Vec3 normalFromLight, float& angleToObject, Vec3 intersectionPoint);
	//void getBounds(Vec3& minimum, Vec3& maximum);
	float getRadius();

	std::string toString();
	//friend std::ostream& operator<<(std::ostream& os, SceneObject const& s);


private:
	float radius;

	void computeBounds();

};

#endif