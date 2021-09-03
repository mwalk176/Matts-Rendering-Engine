#ifndef CAMERA_H
#define CAMERA_H

#include "Vec3.h"

class Camera {
public:

private:
	Vec3 lookFrom;
	Vec3 lookAt;
	Vec3 up;
	double fov;

};

#endif