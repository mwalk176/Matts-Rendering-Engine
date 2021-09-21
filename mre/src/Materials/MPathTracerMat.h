#ifndef MPATHTRACERMAT_H
#define MPATHTRACERMAT_H


#include "Material.h"


class MPathTracerMat : public Material {
public:
	MPathTracerMat();
	MPathTracerMat(Vec3 c);
	MPathTracerMat(Vec3 c, Vec3 e, double i, int t);
	MPathTracerMat(Vec3 c, Vec3 e, double i, int t, double g);

	Vec3 getColor();
	Vec3 getEmission();
	double getIOR();
	int getType();
	double getGamma();

	std::string toString();

private:
	Vec3 color;
	Vec3 emissionColor;
	double IOR;
	int type; //0 diffuse, 1 pure specular, 2 glass
	double gamma;


};





#endif
