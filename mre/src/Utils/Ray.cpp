#include "Ray.h"

Ray::Ray() {
	o = Vec3();
	d = Vec3();
}

Ray::Ray(Vec3 origin, Vec3 direction) {
	o = origin;
	d = direction;
}

Ray::~Ray() {
}

std::ostream& operator<<(std::ostream& os, Ray const& r) {
	os << "{Ray Origin: " << r.o << ", Ray Direction: " << r.d << "}";
	return os;
}
