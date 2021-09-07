#include "Camera.h"

Camera::Camera(int x, int y) {
	lookFrom = Vec3(0); //camera at origin
	lookAt = Vec3(0, 0, 1); //look down positive z-axis
	up = Vec3(0, 1, 0); //positive y-axis is up
	hFov = 60.0;

	rows = y;
	columns = x;
	aspectRatio = columns / rows;
}

Camera::~Camera() {
}

Ray Camera::convertToWorld(double x, double y) {

	double d = 1.0;


	double viewPlaneSizeX = d * tan(hFov);
	double vFov = 2.0 * atan(tan(hFov / 2.0) / aspectRatio);
	double viewPlaneSizeY = d * tan(vFov); 

	return Ray();
}

int Camera::getRows() {
	return rows;
}

int Camera::getColumns() {
	return columns;
}
