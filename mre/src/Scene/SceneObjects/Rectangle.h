#ifndef RECTANGLE_H
#define RECTANGLE_H


#include "SceneObject.h"


class Rectangle : public SceneObject {
public:
	Rectangle(Vec3 p0, Vec3 p1, Vec3 p2, Vec3 p3, Material* mat);
	Rectangle(Vec3 p0, Vec3 p1, Vec3 p2, Vec3 p3, std::vector<Material*> mats);

	bool intersect(Ray r, double& p0, double& p1);
	Vec3 computeNormal(Vec3 intersectionPoint);
	Vec3 getNewDirectionTowardsLight(Vec3 shadowRay, Vec3 alignedNormal, Vec3 normalFromLight, double& angleToObject, Vec3 intersectionPoint);

	std::string toString();

private:
	Vec3 v0, v1, v2, v3;
	Vec3 e0, e1, e2, e3;
	Vec3 eIn0, eIn1, eIn2, eIn3;

	Vec3 normal;

	double D = 0;
	
	bool preComputed = false;
	bool preComputedEdges = false;


};





#endif