#ifndef CAMERA_H
#define CAMERA_H

#include "../Utils/Vec3.h"
#include "../Utils/Ray.h"

class Camera {
public:
	Camera();
	Camera(int x, int y);
	~Camera();

	Ray convertToWorld(double x, double y);
	int getRows();
	int getColumns();

private:
	Vec3 lookFrom;
	Vec3 lookAt;
	Vec3 up;

	double hFov; //horizontal fov
	int rows;
	int columns;
	double aspectRatio;

	Vec3 e1;
	Vec3 e2;
	Vec3 e3;

};

#endif