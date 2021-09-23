#include "Triangle.h"

Triangle::Triangle(Vec3 p0, Vec3 p1, Vec3 p2, Material* mat) {
	v0 = p0;
	v1 = p1;
	v2 = p2;
	pos = (v0 + v1 + v2) / 3.0;
	materials.push_back(mat);
	computeNormal(Vec3(0));

	//std::cout << "Triangle normal: " << normal << "\n";
}

Triangle::Triangle(Vec3 p0, Vec3 p1, Vec3 p2, std::vector<Material*> mats) {
	v0 = p0;
	v1 = p1;
	v2 = p2;
	pos = (v0 + v1 + v2) / 3.0;
	for (int i = 0; i < mats.size(); i++) {
		materials.push_back(mats.at(i));
	}
	computeNormal(Vec3(0));
}

bool Triangle::intersect(Ray r, float& p0, float& p1) {
	if (fabs(normal.dot(r.d)) < 0.001) return false;
	p0 = -(normal.dot(r.o) - D) / normal.dot(r.d);
	//std::cout <<  "Triangle p0: " << p0 << "\n";
	if (p0 < 0) return false;
	Vec3 intersectionPoint = r.o + r.d * p0;

	if (preComputedEdges) {
		Vec3 c0 = intersectionPoint - v0;
		Vec3 c1 = intersectionPoint - v1;
		Vec3 c2 = intersectionPoint - v2;
		float t0 = eIn0.dot(c0);
		float t1 = eIn1.dot(c1);
		float t2 = eIn2.dot(c2);
		if (t0 > 0 && t1 > 0 && t2 > 0) return true;
	} else {
		e0 = v1 - v0;
		e1 = v2 - v1;
		e2 = v0 - v2;
		Vec3 c0 = intersectionPoint - v0;
		Vec3 c1 = intersectionPoint - v1;
		Vec3 c2 = intersectionPoint - v2;
		eIn0 = normal.cross(e0);
		eIn1 = normal.cross(e1);
		eIn2 = normal.cross(e2);
		float t0 = eIn0.dot(c0);
		float t1 = eIn1.dot(c1);
		float t2 = eIn2.dot(c2);
		preComputedEdges = true;
		if (t0 > 0 && t1 > 0 && t2 > 0) return true;

	}



	return false;
}

Vec3 Triangle::computeNormal(Vec3 intersectionPoint) {
	if (preComputedNormal) return normal;
	Vec3 a = v1 - v0; //might need to come back here to make sure the normal is computed properly
	Vec3 b = v2 - v0;
	normal = a.cross(b);
	normal.normalize();

	D = normal.dot(v0);


	preComputedNormal = true;
	return normal;
}

Vec3 Triangle::getNewDirectionTowardsLight(Vec3 shadowRay, Vec3 alignedNormal, Vec3 normalFromLight, float& angleToObject, Vec3 intersectionPoint) {
	//get a random point along both edges of the triangle going away from the first vertex
	Vec3 e0 = v1 - v0;
	Vec3 e1 = v2 - v0;
	float r0 = (float)rand() / RAND_MAX;
	float r1 = (float)rand() / RAND_MAX;
	Vec3 point0 = v0 + e0 * r0;
	Vec3 point1 = v1 + e1 * r1;

	//get the vector between those two random points
	Vec3 e2 = point1 - point0;
	float r2 = (float)rand() / RAND_MAX;

	//get a random point along that vector
	Vec3 randomPoint = point0 + e2 * r2;
	//congrats! you've sampled a random point in the triangle!

	Vec3 newShadowRay = randomPoint - intersectionPoint;
	newShadowRay.normalize();

	angleToObject = 0.9;

	return newShadowRay;
}

std::string Triangle::toString() {
	return "TRIANGLE";
}
