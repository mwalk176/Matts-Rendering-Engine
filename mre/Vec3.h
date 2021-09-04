#ifndef VEC3_H
#define VEC3_H

#include <ostream>
#include <sstream>
#include <fstream>
#include <iostream>


class Vec3 {
public:
	double x;
	double y;
	double z;

	Vec3();
	Vec3(double num);
	Vec3(double inX, double inY, double inZ);

	Vec3 operator + (const Vec3 v);
	Vec3 operator - (const Vec3 v);
	Vec3 operator * (const Vec3 v);
	Vec3 operator * (const float c);
	Vec3 operator / (const float c);

	float dot(Vec3 v);
	void normalize();
	float calculateMagnitude();
	void setAll(float val);
	void setEach(float xNew, float yNew, float zNew);

	friend std::ostream& operator<<(std::ostream& os, Vec3 const& v); 
};

#endif