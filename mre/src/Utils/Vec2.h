#ifndef VEC2_H
#define VEC2_H

#include <ostream>
#include <sstream>
#include <fstream>
#include <iostream>


class Vec2 {
public:	
	float u;
	float v;

	Vec2();
	Vec2(float num);
	Vec2(float inU, float inV);

	Vec2 operator + (const Vec2 vec);
	Vec2 operator - (const Vec2 vec);
	Vec2 operator * (const Vec2 vec);
	Vec2 operator * (const float c);
	Vec2 operator / (const float c);

	float dot(Vec2 vec);
	//Vec2 cross(Vec2 vec);
	void normalize();
	float calculateMagnitude();
	void setAll(float val);
	void setEach(float uNew, float vNew);
	void clamp();



	friend std::ostream& operator<<(std::ostream& os, Vec2 const& vec);
};

#endif