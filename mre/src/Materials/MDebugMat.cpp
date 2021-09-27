#include "MDebugMat.h"

MDebugMat::MDebugMat() {
    color = Vec3(((float)rand() / RAND_MAX), ((float)rand() / RAND_MAX), ((float)rand() / RAND_MAX));
    matType = 0;
}

MDebugMat::MDebugMat(Vec3 c) {
    color = c;
    matType = 0;
}

Vec3 MDebugMat::getColor() {
    return color;
}

std::string MDebugMat::toString() {
    return "MDEBUGMAT";
}
