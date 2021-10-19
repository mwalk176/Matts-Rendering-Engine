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

void SceneObject::getBounds(Vec3& minimum, Vec3& maximum) {
    minimum = min;
    maximum = max;
}

Material* SceneObject::getMaterial(int mType) {
    if (primaryMaterial == nullptr) {
        for (int i = 0; i < materials.size(); i++) {
            if (materials[i]->matType == mType) {
                primaryMaterial = materials[i];
                return materials[i];
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
