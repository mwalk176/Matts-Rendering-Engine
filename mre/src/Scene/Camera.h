#ifndef CAMERA_H
#define CAMERA_H

#include "../Utils/Vec3.h"
#include "../Utils/Ray.h"

class Camera {
public:
	Camera();
	~Camera();

	Ray convertToWorld(double x, double y);

private:
	Vec3 lookFrom;
	Vec3 lookAt;
	Vec3 up;
	double fov;

};

#endif