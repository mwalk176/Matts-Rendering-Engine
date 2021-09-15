#include "Triangle.h"

Triangle::Triangle(Vec3 p0, Vec3 p1, Vec3 p2, Material* mat) {
	v0 = p0;
	v1 = p1;
	v2 = p2;
	pos = (v0 + v1 + v2) / 3.0;
	materials.push_back(mat);
	computeNormal(Vec3(0));

	std::cout << "Triangle normal: " << normal << "\n";
}

bool Triangle::intersect(Ray r, double& p0, double& p1) {
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

std::string Triangle::toString() {
	return "TRIANGLE";
}
