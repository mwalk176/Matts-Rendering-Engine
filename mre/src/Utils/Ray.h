#ifndef RAY_H
#define RAY_H

#include "Vec3.h"

class Ray {
public:
	Ray();
	Ray(Vec3 origin, Vec3 direction);
	~Ray();

	Vec3 o; //origin
	Vec3 d; //direction
	Vec3 inv; //inverse of the direction
	int sign[3]; //sign of the three components of the inverse


	friend std::ostream& operator<<(std::ostream& os, Ray const& r);

private:

};

#endif
