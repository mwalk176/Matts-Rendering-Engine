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

private:

};

#endif
