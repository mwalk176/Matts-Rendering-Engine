#include "SceneObject.h"

Vec3 SceneObject::getPos() {
    return pos;
}

std::vector<Material*> SceneObject::getMaterials() {
    return materials;
}
