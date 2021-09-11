#include "MDebug.h"

Vec3 MDebug::render(Ray camRay, Scene& scene) {

    double closestPoint = INFINITY;
    SceneObject* closestObject = scene.getClosestObject(camRay, closestPoint);
    if (closestObject == nullptr) { //nothing was hit
        return Vec3();
    }
    else { //compute lighting for closestObject
        //std::cout << "HIT!" << std::endl;
        MDebugMat* mat = nullptr;
        std::vector<Material*> materials = closestObject->getMaterials();
        for(int i = 0; i < materials.size(); i++) {
            if (materials.at(i)->toString() == "MDEBUGMAT") {
                mat = static_cast<MDebugMat*>(materials.at(i));
                break;
            }
        }
        if (mat == nullptr) return Vec3();

        return mat->getColor();
    }
}
