#include "Rectangle.h"

Rectangle::Rectangle(Vec3 p0, Vec3 p1, Vec3 p2, Vec3 p3, Material* mat) {
	v0 = p0; //DO THESE CLOCKWISE
	v1 = p1;
	v2 = p2;
	v3 = p3;
	pos = (v0 + v1 + v2 + v3) / 4.0;
	materials.push_back(mat);
	computeNormal(Vec3());
	//std::cout << "Rectangle normal: " << normal << "\n";
	shapeType = 2;
}

Rectangle::Rectangle(Vec3 p0, Vec3 p1, Vec3 p2, Vec3 p3, std::vector<Material*> mats) {
	v0 = p0; //DO THESE CLOCKWISE
	v1 = p1;
	v2 = p2;
	v3 = p3;
	pos = (v0 + v1 + v2 + v3) / 4.0;
	for (int i = 0; i < mats.size(); i++) {
		materials.push_back(mats[i]);
	}
	computeNormal(Vec3());
	shapeType = 2;
}

bool Rectangle::intersect(Ray r, float& p0, float& p1) {
	if (fabs(normal.dot(r.d)) < 0.001) return false;
	p0 = -(normal.dot(r.o) - D) / normal.dot(r.d);
	//std::cout <<  "Rectangle p0: " << p0 << "\n";
	if (p0 < 0) return false;
	Vec3 intersectionPoint = r.o + r.d * p0;

	if (preComputedEdges) {
		Vec3 c0 = intersectionPoint - v0;
		Vec3 c1 = intersectionPoint - v1;
		Vec3 c2 = intersectionPoint - v2;
		Vec3 c3 = intersectionPoint - v3;
		float t0 = eIn0.dot(c0);
		float t1 = eIn1.dot(c1);
		float t2 = eIn2.dot(c2);
		float t3 = eIn3.dot(c3);
		if (t0 > 0 && t1 > 0 && t2 > 0 && t3 > 0) return true;
	} else {
		e0 = v1 - v0;
		e1 = v2 - v1;
		e2 = v3 - v2;
		e3 = v0 - v3;
		Vec3 c0 = intersectionPoint - v0;
		Vec3 c1 = intersectionPoint - v1;
		Vec3 c2 = intersectionPoint - v2;
		Vec3 c3 = intersectionPoint - v3;
		eIn0 = normal.cross(e0);
		eIn1 = normal.cross(e1);
		eIn2 = normal.cross(e2);
		eIn3 = normal.cross(e3);
		float t0 = eIn0.dot(c0);
		float t1 = eIn1.dot(c1);
		float t2 = eIn2.dot(c2);
		float t3 = eIn3.dot(c3);
		if (t0 > 0 && t1 > 0 && t2 > 0 && t3 > 0) return true;
		preComputedEdges = true;
	}

	return false;

}

Vec3 Rectangle::computeNormal(Vec3 intersectionPoint) {
	if (preComputed) return normal;
	Vec3 a = v1 - v0; //might need to come back here to make sure the normal is computed properly
	Vec3 b = v3 - v0;
	normal = a.cross(b);
	normal.normalize();

	D = normal.dot(v0);


	preComputed = true;
	return normal;
}

Vec3 Rectangle::getNewDirectionTowardsLight(Vec3 shadowRay, Vec3 alignedNormal, Vec3 normalFromLight, float& angleToObject, Vec3 intersectionPoint) {
	return shadowRay;
}

std::string Rectangle::toString() {
	return "RECTANGLE";
}
