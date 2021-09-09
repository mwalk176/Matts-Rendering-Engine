#include "MDebug.h"

Vec3 MDebug::render(Ray camRay, Scene& scene) {

    std::vector<SceneObject*> objects = scene.getObjects();
    for (int i = 0; i < objects.size(); i++) {
        SceneObject* object = objects.at(i);

        double p0 = INFINITY;
        double p1 = INFINITY;

        if(object->intersect(camRay, p0, p1))
    }

    return Vec3();
}
