#include "PointLight.h"

PointLight::PointLight() {
    pos = Vec3();
}

PointLight::PointLight(Vec3 p) {
    pos = p;
}

Vec3 PointLight::getPos() {
    return pos;
}

std::string PointLight::toString() {
    return "POINT_LIGHT";
}
