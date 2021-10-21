#include "Ray.h"

Ray::Ray() {
	o = Vec3();
	d = Vec3();
	inv = Vec3();
	sign[0] = 0;
	sign[1] = 0;
	sign[2] = 0;
}

Ray::Ray(Vec3 origin, Vec3 direction) {
	o = origin;
	d = direction;
	float invX = 1 / direction.x;
	float invY = 1 / direction.y;
	float invZ = 1 / direction.z;
	inv = Vec3(invX, invY, invZ);
	sign[0] = (invX < 0);
	sign[1] = (invY < 0);
	sign[2] = (invZ < 0);
}

Ray::~Ray() {
}

std::ostream& operator<<(std::ostream& os, Ray const& r) {
	os << "{Ray Origin: " << r.o << ", Ray Direction: " << r.d << "}";
	return os;
}
