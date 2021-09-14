#include "SceneObject.h"

SceneObject::SceneObject() {
    materials.push_back(new MDebugMat());
    //materials.push_back(new MRayTracerMat());
}

Vec3 SceneObject::getPos() {
    return pos;
}

std::vector<Material*> SceneObject::getMaterials() {
    return materials;
}
