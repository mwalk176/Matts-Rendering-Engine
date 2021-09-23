#ifndef VEC3_H
#define VEC3_H

#include <ostream>
#include <sstream>
#include <fstream>
#include <iostream>


class Vec3 {
public:
	float x;
	float y;
	float z;

	Vec3();
	Vec3(float num);
	Vec3(float inX, float inY, float inZ);

	Vec3 operator + (const Vec3 v);
	Vec3 operator - (const Vec3 v);
	Vec3 operator * (const Vec3 v);
	Vec3 operator * (const float c);
	Vec3 operator / (const float c);

	float dot(Vec3 v);
	Vec3 cross(Vec3 v); 
	void normalize();
	float calculateMagnitude();
	void setAll(float val);
	void setEach(float xNew, float yNew, float zNew);
	void clamp(); 

	

	friend std::ostream& operator<<(std::ostream& os, Vec3 const& v); 
};

#endif