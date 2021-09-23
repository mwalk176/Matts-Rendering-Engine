#ifndef MRAYTRACERMAT_H
#define MRAYTRACERMAT_H

#include "Material.h"

class MRayTracerMat : public Material {
public:
	MRayTracerMat();
	MRayTracerMat(Vec3 c);
	MRayTracerMat(Vec3 c, float i, int t);

	Vec3 getColor();
	float getIOR();
	int getType();

	std::string toString();

private:
	Vec3 color;
	float IOR;
	int type; //0 diffuse, 1 pure specular, 2 glass


};





#endif