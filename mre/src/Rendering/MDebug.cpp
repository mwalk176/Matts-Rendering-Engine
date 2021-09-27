#include "MDebug.h"

MDebug::MDebug() {
}

MDebug::MDebug(Scene* s) {
    scene = s;
}

Vec3 MDebug::render(Ray camRay) {

    float closestPoint = INFINITY;
    SceneObject* closestObject = scene->getClosestObject(camRay, closestPoint);
    if (closestObject == nullptr) { //nothing was hit
        return Vec3();
    }

    //compute lighting for closestObject
    //std::cout << "HIT!" << std::endl;

    MDebugMat* mat = nullptr;
    std::vector<Material*> materials = closestObject->getMaterials();

    for(int i = 0; i < materials.size(); i++) {
        if (materials[i]->toString() == "MDEBUGMAT") {
            mat = static_cast<MDebugMat*>(materials[i]);
            break;
        }
    }
    if (mat == nullptr) return Vec3();

    return mat->getColor();
    
}
