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

	Ray convertToWorld(float x, float y);
	int getRows();
	int getColumns();
	
	Vec3 getStart();
	Vec3 getIncX();
	Vec3 getIncY();

	void setCameraCoords(Vec3 lf, Vec3 la, Vec3 u, float f);


private:
	void buildCoordinateSpace();

	Vec3 lookFrom;
	Vec3 lookAt;
	Vec3 up;

	float fov; //horizontal fov
	int rows;
	int columns;
	float aspectRatio;

	Vec3 e1;
	Vec3 e2;
	Vec3 e3;

	Vec3 start;
	Vec3 incX;
	Vec3 incY;


	const float pi = acos(-1);

};

#endif