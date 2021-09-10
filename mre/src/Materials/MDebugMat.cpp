#include "MDebugMat.h"

MDebugMat::MDebugMat(Vec3 c) {
    color = c;
}

Vec3 MDebugMat::getColor() {
    return color;
}

std::string MDebugMat::toString() {
    return "MDEBUGMAT";
}
