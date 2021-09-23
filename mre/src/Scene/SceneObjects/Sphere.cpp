#include "Sphere.h"

Sphere::Sphere() {
	pos = Vec3(0);
	radius = 1.0;
}

Sphere::Sphere(Vec3 p) {
	pos = p;
	radius = 1;
}

Sphere::Sphere(Vec3 p, float r) {
	pos = p;
	radius = r;
}

Sphere::Sphere(Vec3 p, float r, Material* mat) {
	pos = p;
	radius = r;
	materials.push_back(mat);
}

Sphere::Sphere(Vec3 p, float r, std::vector<Material*> mats) {
	pos = p;
	radius = r;
	for (int i = 0; i < mats.size(); i++) {
		materials.push_back(mats.at(i));
	}
	
}

Vec3 Sphere::getPos() {
    return Vec3();
}

bool Sphere::intersect(Ray r, float& p0, float& p1) {
	//analytic way
	float a = r.d.dot(r.d); //should be 1
	Vec3 D2 = r.d * 2;
	Vec3 PR = r.o - pos; //vector from the sphere's center to the rayOrigin
	float b = D2.dot(PR);
	float c = PR.dot(PR) - (radius * radius);
	float discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0) return false; // the ray didn't hit the sphere
	if (discriminant == 0) { // then it has only one hit
		p0 = (-1 * b) / (2 * a);
		p1 = p0;

	}
	if (discriminant > 0) { // then it has two hits
		int sign = 1;
		if (b < 0) sign = -1;
		float quadratic = (-0.5) * ((float)b + (float)sign * sqrt(discriminant));
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

Vec3 Sphere::getNewDirectionTowardsLight(Vec3 shadowRay, Vec3 alignedNormal, Vec3 normalFromLight, float& angleToObject, Vec3 intersectionPoint) {
	//build a coordinate space in the hemisphere of the shadowray light
	Vec3 se1 = Vec3(0);
	if (fabs(alignedNormal.x) > fabs(alignedNormal.y)) {
		se1 = Vec3(shadowRay.z, 0, -shadowRay.x) / sqrt(shadowRay.x * shadowRay.x + shadowRay.z * shadowRay.z);
	}
	else {
		se1 = Vec3(0, -shadowRay.z, shadowRay.y) / sqrt(shadowRay.y * shadowRay.y + shadowRay.z * shadowRay.z);
	}
	se1.normalize();
	Vec3 se2 = shadowRay.cross(se1);
	se2.normalize();

	//calculate a random direction towards light
	angleToObject = sqrt(1 - radius * radius / normalFromLight.dot(normalFromLight));
	float randX = (float)rand() / RAND_MAX; //get us a random point
	float randomAngle2 = M_PI * 2 * ((float)rand() / RAND_MAX);
	float angleCos = 1 - randX + randX * angleToObject;
	float angleSin = sqrt(1 - angleCos * angleCos);
	Vec3 newShadowRay = se1 * cos(randomAngle2) * angleSin + se2 * sin(randomAngle2) * angleSin + shadowRay * angleCos;
	newShadowRay.normalize();

	return newShadowRay;
}

float Sphere::getRadius() {
	return radius;
}


std::string Sphere::toString() {
    std::string output = "SPHERE";
    return output;
}
