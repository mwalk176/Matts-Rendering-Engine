#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {
    lightDirection = Vec3(1, -1, 0);
    lightType = 1;
}

DirectionalLight::DirectionalLight(Vec3 d) {
    lightDirection = d;
    lightType = 1;
}

Vec3 DirectionalLight::getLightDirection() {
    return lightDirection;
}

std::string DirectionalLight::toString() {
    return "DIRECTIONAL_LIGHT";
}
