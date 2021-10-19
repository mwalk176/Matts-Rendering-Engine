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
	computeBounds();
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
	computeBounds();
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

void Rectangle::computeBounds() {
	float xMin, yMin, zMin;
	float xMax, yMax, zMax;

	//find absolute minimum values from the 3 points
	xMin = v0.x;
	yMin = v0.y;
	zMin = v0.z;

	if (v1.x < xMin) xMin = v1.x;
	if (v2.x < xMin) xMin = v2.x;
	if (v3.x < xMin) xMin = v3.x;

	if (v1.y < yMin) yMin = v1.y;
	if (v2.y < yMin) yMin = v2.y;
	if (v3.y < yMin) yMin = v3.y;

	if (v1.z < zMin) zMin = v1.z;
	if (v2.z < zMin) zMin = v2.z;
	if (v3.z < zMin) zMin = v3.z;



	//find absolute maximum values from the 3 points
	xMax = v0.x;
	yMax = v0.y;
	zMax = v0.z;

	if (v1.x > xMax) xMax = v1.x;
	if (v2.x > xMax) xMax = v2.x;
	if (v3.x > xMax) xMax = v3.x;

	if (v1.y > yMax) yMax = v1.y;
	if (v2.y > yMax) yMax = v2.y;
	if (v3.y > yMax) yMax = v3.y;

	if (v1.z > zMax) zMax = v1.z;
	if (v2.z > zMax) zMax = v2.z;
	if (v3.z > zMax) zMax = v3.z;

	min = Vec3(xMin, yMin, zMin);
	max = Vec3(xMax, yMax, zMax);

	std::cout << "Rectangle Min: " << min << "\n";
	std::cout << "Rectangle Max: " << max << "\n\n";
}
