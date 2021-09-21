#include "MPathTracerMat.h"

MPathTracerMat::MPathTracerMat() {
	color = Vec3(1);
	emissionColor = Vec3();
	IOR = 1.5;
	type = 0;
	gamma = 1.0;
}

MPathTracerMat::MPathTracerMat(Vec3 c) {
	color = c;
	emissionColor = Vec3();
	IOR = 1.5;
	type = 0;
	gamma = 1.0;
}

MPathTracerMat::MPathTracerMat(Vec3 c, Vec3 e, double i, int t) {
	color = c;
	emissionColor = e;
	IOR = i;
	type = t;
	gamma = 1.0;
}

MPathTracerMat::MPathTracerMat(Vec3 c, Vec3 e, double i, int t, double g) {
	color = c;
	emissionColor = e;
	IOR = i;
	type = t;
	gamma = g;
}

Vec3 MPathTracerMat::getColor() {
	return color;
}

Vec3 MPathTracerMat::getEmission() {
	return emissionColor;
}

double MPathTracerMat::getIOR() {
	return IOR;
}

int MPathTracerMat::getType() {
	return type;
}

double MPathTracerMat::getGamma() {
	return gamma;
}

std::string MPathTracerMat::toString() {
	return "MPATHTRACERMAT";
}
