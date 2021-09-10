#include "Camera.h"

Camera::Camera() {
	lookFrom = Vec3(0,0,0); //camera at origin
	lookAt = Vec3(0, 0, 1); //COORDINATES of where you want the camera to look at
	up = Vec3(0, 1, 0); //positive y-axis is up
	fov = 60.0;

	rows = 256;
	columns = 256;
	aspectRatio = columns / rows;
}

//Camera Camera::operator=(const Camera& c) {
//	Camera cam = Camera();
//	cam.lookFrom = c.lookFrom;
//	cam.lookAt = c.lookAt;
//	cam.up = c.up;
//	cam.fov = c.fov;
//	cam.rows = c.rows;
//	cam.columns = c.columns;
//	cam.aspectRatio = c.aspectRatio;
//	return cam;
//}

Camera::Camera(int x, int y) {
	lookFrom = Vec3(0, 0, 0); //camera at origin
	lookAt = Vec3(0, 0, 1); //look down positive z-axis
	up = Vec3(0, 1, 0); //positive y-axis is up
	fov = 60.0;

	rows = y;
	columns = x;
	aspectRatio = columns / rows;

	buildCoordinateSpace();
}

Camera::~Camera() {
}

Ray Camera::convertToWorld(double x, double y) {

	Vec3 xVec = incX * x;
	Vec3 yVec = incY * y;
	
	Vec3 worldVec = start + xVec - yVec;
	Ray r(lookFrom, worldVec);

	/*double d = 1.0;


	double viewPlaneSizeX = d * tan(fov);
	double vFov = 2.0 * atan(tan(fov / 2.0) / aspectRatio);
	double viewPlaneSizeY = d * tan(vFov); */

	return r;
}

int Camera::getRows() {
	return rows;
}

int Camera::getColumns() {
	return columns;
}

Vec3 Camera::getStart() {
	return start;
}

Vec3 Camera::getIncX() {
	return incX;
}

Vec3 Camera::getIncY() {
	return incY;
}

void Camera::buildCoordinateSpace() {
	e3 = lookAt - lookFrom;
	e1 = e3.cross(up);
	e2 = e1.cross(e3);
	
	e1 = e1 * -1.0; //flip to left-handed coordinate system

	std::cout << "e1: " << e1 << std::endl;
	std::cout << "e2: " << e2 << std::endl;
	std::cout << "e3: " << e3 << std::endl;

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
