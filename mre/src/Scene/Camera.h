#ifndef CAMERA_H
#define CAMERA_H

#include "../Utils/Vec3.h"
#include "../Utils/Ray.h"
#include <cmath>

class Camera {
public:
	Camera();
	//Camera(const Camera& c);

	//Camera operator = (const Camera& c);

	Camera(int x, int y);
	~Camera();

	Ray convertToWorld(double x, double y);
	int getRows();
	int getColumns();
	
	Vec3 getStart();
	Vec3 getIncX();
	Vec3 getIncY();

	void setCameraCoords(Vec3 lf, Vec3 la, Vec3 u, double f);


private:
	void buildCoordinateSpace();

	Vec3 lookFrom;
	Vec3 lookAt;
	Vec3 up;

	double fov; //horizontal fov
	int rows;
	int columns;
	double aspectRatio;

	Vec3 e1;
	Vec3 e2;
	Vec3 e3;

	Vec3 start;
	Vec3 incX;
	Vec3 incY;


	const double pi = acos(-1);

};

#endif