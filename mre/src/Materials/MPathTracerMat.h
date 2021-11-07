#ifndef MPATHTRACERMAT_H
#define MPATHTRACERMAT_H


#include "Material.h"
#include "../Image/Image.h"


class MPathTracerMat : public Material {
public:
	MPathTracerMat();
	MPathTracerMat(Vec3 c);
	MPathTracerMat(Vec3 c, Vec3 e, float i, int t);
	MPathTracerMat(Vec3 c, Vec3 e, float i, int t, float g);
	MPathTracerMat(Vec3 c, Vec3 e, float i, int t, float g, float r);
	MPathTracerMat(Image tex, Vec3 e, float i, int t, float g, float r);

	Vec3 getColor();
	Vec3 getColor(float u, float v);
	//Vec3 getEmission();
	//float getIOR();
	//int getType();
	//float getGamma();

	Vec3 color;
	Vec3 emissionColor;
	float IOR;
	int type; //0 diffuse, 1 pure specular, 2 glass
	float gamma;
	float roughness;
	Image texture;

	std::string toString();

private:



};





#endif
