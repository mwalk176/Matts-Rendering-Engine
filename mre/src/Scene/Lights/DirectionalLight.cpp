#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {
    lightDirection = Vec3(1, -1, 0);
}

DirectionalLight::DirectionalLight(Vec3 d) {
    lightDirection = d;
}

Vec3 DirectionalLight::getLightDirection() {
    return lightDirection;
}

std::string DirectionalLight::toString() {
    return "DIRECTIONAL_LIGHT";
}
