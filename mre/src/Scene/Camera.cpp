#include "Camera.h"

Camera::Camera() {
	lookFrom = Vec3(0); //camera at origin
	lookAt = Vec3(0, 0, 1); //look down positive z-axis
	up = Vec3(0, 1, 0); //positive y-axis is up
	fov = 60.0;
}

Camera::~Camera() {
}

Ray Camera::convertToWorld(double x, double y) {
	return Ray();
}
