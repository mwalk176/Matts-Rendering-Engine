#include "PointLight.h"

PointLight::PointLight() {
    pos = Vec3();
}

Vec3 PointLight::getPos() {
    return pos;
}

std::string PointLight::toString() {
    return "POINT_LIGHT";
}
