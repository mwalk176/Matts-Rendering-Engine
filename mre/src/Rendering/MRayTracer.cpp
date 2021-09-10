#include "MRayTracer.h"

Vec3 MRayTracer::render(Ray camRay, Scene& scene) {

    double closestPoint = INFINITY;
    SceneObject* closestObject = scene.getClosestObject(camRay, closestPoint);

    if (closestObject == nullptr) { //nothing was hit
        return Vec3();
    }




    //compute lighting for closestObject
    //check if light
    //calculate intersection spot and normal

    
}
