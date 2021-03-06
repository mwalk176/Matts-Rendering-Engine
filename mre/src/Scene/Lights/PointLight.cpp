#include "PointLight.h"

PointLight::PointLight() {
    pos = Vec3();
    lightType = 0;
}

PointLight::PointLight(Vec3 p) {
    pos = p;
    lightType = 0;
}

Vec3 PointLight::getPos() {
    return pos;
}

std::string PointLight::toString() {
    return "POINT_LIGHT";
}
