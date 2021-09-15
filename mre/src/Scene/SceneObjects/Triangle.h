#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "SceneObject.h"


class Triangle : public SceneObject {
public:
	Triangle(Vec3 p0, Vec3 p1, Vec3 p2, Material* mat);
	bool intersect(Ray r, double& p0, double& p1);
	Vec3 computeNormal(Vec3 intersectionPoint);

	std::string toString();


private:
	Vec3 v0, v1, v2;
	Vec3 e0, e1, e2;
	Vec3 eIn0, eIn1, eIn2;

	Vec3 normal;

	float D = 0;
	
	bool preComputedNormal = false;
	bool preComputedEdges = false;


};





#endif