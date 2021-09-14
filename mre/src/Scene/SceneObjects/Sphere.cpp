#include "Sphere.h"

Sphere::Sphere() {
	pos = Vec3(0);
	radius = 1.0;
}

Sphere::Sphere(Vec3 p) {
	pos = p;
	radius = 1;
}

Sphere::Sphere(Vec3 p, double r) {
	pos = p;
	radius = r;
}

Sphere::Sphere(Vec3 p, double r, Material* mat) {
	pos = p;
	radius = r;
	materials.push_back(mat);
}

Vec3 Sphere::getPos() {
    return Vec3();
}

bool Sphere::intersect(Ray r, double& p0, double& p1) {
	//analytic way
	double a = r.d.dot(r.d); //should be 1
	Vec3 D2 = r.d * 2;
	Vec3 PR = r.o - pos; //vector from the sphere's center to the rayOrigin
	double b = D2.dot(PR);
	double c = PR.dot(PR) - (radius * radius);
	double discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0) return false; // the ray didn't hit the sphere
	if (discriminant == 0) { // then it has only one hit
		p0 = (-1 * b) / (2 * a);
		p1 = p0;

	}
	if (discriminant > 0) { // then it has two hits
		int sign = 1;
		if (b < 0) sign = -1;
		double quadratic = (-0.5) * ((double)b + (double)sign * sqrt(discriminant));
		p0 = quadratic / a;
		p1 = c / quadratic;

	}

	if (p0 > p1) std::swap(p0, p1);
	if (p0 < 0) {
		if (p1 < 0) return false;
		p0 = p1;
	}
	return true;



		
}

Vec3 Sphere::computeNormal(Vec3 intersectionPoint) {
	return intersectionPoint - pos;
}


std::string Sphere::toString() {
    std::string output = "Sphere";
    return output;
}
