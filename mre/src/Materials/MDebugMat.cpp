#include "MDebugMat.h"

MDebugMat::MDebugMat() {
    color = Vec3(rand(), rand(), rand());
}

MDebugMat::MDebugMat(Vec3 c) {
    color = c;
}

Vec3 MDebugMat::getColor() {
    return color;
}

std::string MDebugMat::toString() {
    return "MDEBUGMAT";
}
