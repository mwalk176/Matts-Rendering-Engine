#include "Camera.h"

Camera::Camera() {
}

Camera::Camera(int x, int y) {
	lookFrom = Vec3(0); //camera at origin
	lookAt = Vec3(0, 0, 1); //look down positive z-axis
	up = Vec3(0, 1, 0); //positive y-axis is up
	fov = 60.0;

	rows = y;
	columns = x;
	aspectRatio = columns / rows;
}

Camera::~Camera() {
}

Ray Camera::convertToWorld(double x, double y) {

	Vec3 xVec = incX * x;
	Vec3 yVec = incY * y;
	
	Vec3 worldVec = start + xVec + yVec;
	Ray r(lookFrom, worldVec);

	/*double d = 1.0;


	double viewPlaneSizeX = d * tan(fov);
	double vFov = 2.0 * atan(tan(fov / 2.0) / aspectRatio);
	double viewPlaneSizeY = d * tan(vFov); */

	return r;
}

const int Camera::getRows() {
	return rows;
}

const int Camera::getColumns() {
	return columns;
}

const Vec3 Camera::getStart() {
	return start;
}

const Vec3 Camera::getIncX() {
	return incX;
}

const Vec3 Camera::getIncY() {
	return incY;
}

void Camera::buildCoordinateSpace() {
	e3 = lookAt - lookFrom;
	e1 = e3.cross(up);
	e2 = e1.cross(e3);

	double d = e3.calculateMagnitude();
	double viewPlaneSizeX = d * tan(fov * (pi / 180.0));
	double viewPlaneSizeY = viewPlaneSizeX * rows / columns;

	e1.normalize();
	e2.normalize();
	e3.normalize();

	incX = e1 * (2 * viewPlaneSizeX) / columns;
	incY = e2 * (2 * viewPlaneSizeY) / rows;
	start = lookAt - incX * (columns / 2.0 - 0.5) + incY * (rows / 2.0 - 0.5);
}
