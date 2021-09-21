#include "SceneObject.h"

//Material* SceneObject::primaryMaterial;

SceneObject::SceneObject() {
    materials.push_back(new MDebugMat());
    primaryMaterial = nullptr;
    //materials.push_back(new MRayTracerMat());
}

Vec3 SceneObject::getPos() {
    return pos;
}

Material* SceneObject::getMaterial(std::string mType) {
    if (primaryMaterial == nullptr) {
        for (int i = 0; i < materials.size(); i++) {
            if (materials.at(i)->toString() == mType) {
                primaryMaterial = materials.at(i);
                return materials.at(i);
            }
        }
        return nullptr;
    }
    return primaryMaterial;

}

void SceneObject::setPrimaryMaterial(Material* m) {
    primaryMaterial = m;
}

std::vector<Material*> SceneObject::getMaterials() {
    return materials;
}
