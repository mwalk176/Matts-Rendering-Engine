#include "SceneObject.h"

SceneObject::SceneObject() {
    materials.push_back(new MDebugMat());
}

Vec3 SceneObject::getPos() {
    return pos;
}

std::vector<Material*> SceneObject::getMaterials() {
    return materials;
}
