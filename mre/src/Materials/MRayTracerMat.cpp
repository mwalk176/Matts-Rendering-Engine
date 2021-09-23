#include "MRayTracerMat.h"

MRayTracerMat::MRayTracerMat() { //creates a default white diffuse material
    color = Vec3(1);
    IOR = 1.5;
    type = 0;
}

MRayTracerMat::MRayTracerMat(Vec3 c) {
    color = c;
    IOR = 1.5;
    type = 0;
}

MRayTracerMat::MRayTracerMat(Vec3 c, float i, int t) {
    color = c;
    IOR = i;
    type = t;
}

Vec3 MRayTracerMat::getColor() {
    return color;
}

float MRayTracerMat::getIOR() {
    return IOR;
}

int MRayTracerMat::getType() {
    return type;
}

std::string MRayTracerMat::toString() {
    return "MRAYTRACERMAT";
}
