#include "MPathTracerMat.h"

MPathTracerMat::MPathTracerMat() {
	color = Vec3(1);
	emissionColor = Vec3();
	IOR = 1.5;
	type = 0;
	gamma = 1.0;
	matType = 2;
	roughness = 0;
}

MPathTracerMat::MPathTracerMat(Vec3 c) {
	color = c;
	emissionColor = Vec3();
	IOR = 1.5;
	type = 0;
	gamma = 1.0;
	matType = 2;
	roughness = 0;
}

MPathTracerMat::MPathTracerMat(Vec3 c, Vec3 e, float i, int t) {
	color = c;
	emissionColor = e;
	IOR = i;
	type = t;
	gamma = 1.0;
	matType = 2;
	roughness = 0;
}

MPathTracerMat::MPathTracerMat(Vec3 c, Vec3 e, float i, int t, float g) {
	color = c;
	emissionColor = e;
	IOR = i;
	type = t;
	gamma = g;
	matType = 2;
	roughness = 0;
}

MPathTracerMat::MPathTracerMat(Vec3 c, Vec3 e, float i, int t, float g, float r) {
	color = c;
	emissionColor = e;
	IOR = i;
	type = t;
	gamma = g;
	matType = 2;
	roughness = r;
}

MPathTracerMat::MPathTracerMat(Image tex, Vec3 e, float i, int t, float g, float r) {
	texture = tex;
	color = Vec3();
	emissionColor = e;
	IOR = i;
	type = t;
	gamma = g;
	matType = 2;
	roughness = r;
}

Vec3 MPathTracerMat::getColor() {
	return color;
}

Vec3 MPathTracerMat::getColor(float u, float v) {
	return texture.get(u, v);
}

//Vec3 MPathTracerMat::getColor() {
//	return color;
//}
//
//Vec3 MPathTracerMat::getEmission() {
//	return emissionColor;
//}
//
//float MPathTracerMat::getIOR() {
//	return IOR;
//}
//
//int MPathTracerMat::getType() {
//	return type;
//}
//
//float MPathTracerMat::getGamma() {
//	return gamma;
//}

std::string MPathTracerMat::toString() {
	return "MPATHTRACERMAT";
}
