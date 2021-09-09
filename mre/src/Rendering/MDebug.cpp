#include "MDebug.h"

Vec3 MDebug::render(Ray camRay, Scene& scene) {

    double closestPoint = INFINITY;
    SceneObject* closestObject = scene.getClosestObject(camRay, closestPoint);
    if (closestObject == nullptr) { //nothing was hit
        return Vec3();
    }
    else { //compute lighting for closestObject
        //std::cout << "HIT!" << std::endl;
        return Vec3(0,.5,1);
    }
}
