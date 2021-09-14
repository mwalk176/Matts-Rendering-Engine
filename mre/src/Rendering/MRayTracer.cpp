#include "MRayTracer.h"

Vec3 MRayTracer::render(Ray camRay, Scene& scene) {

    Vec3 col = trace(camRay, scene, 1);
    return col;



    
}

Vec3 MRayTracer::trace(Ray ray, Scene& scene, int depth) {

    depth++; //increment depth

    double epsilon = 8e-5;

    //first find closest object (if there is one)
    double closestPoint = INFINITY;
    SceneObject* closestObject = scene.getClosestObject(ray, closestPoint);

    if (closestObject == nullptr) return Vec3(); //nothing was hit

    
    //compute intersection point and normal and determine if it's inside an object
    Vec3 intersectionPoint = ray.o + ray.d * closestPoint;
    Vec3 normal = closestObject->computeNormal(intersectionPoint);
    normal.normalize();
    Vec3 alignedNormal = normal;
    bool outsideSphere = true;
    if (normal.dot(ray.d) >= 0) {
        outsideSphere = false;
        alignedNormal = normal * -1;
    }

    Vec3 normalOrigin = intersectionPoint + normal * epsilon;
    Ray normalRay(normalOrigin, normal);


    //then get that object's material
    MRayTracerMat* mat = static_cast<MRayTracerMat*>(getMaterial(closestObject->getMaterials()));
    if (mat == nullptr) return Vec3(); //no compatible material found
    Vec3 objectColor = mat->getColor();

    switch (mat->getType()) {
    case 0: { //difuse

        std::vector<Light*> lights = scene.getLights();

        double lightIntensity = 0;

        for (unsigned int i = 0; i < lights.size(); i++) {
            
            double lightDist = INFINITY;
            Vec3 shadowRay;

            //check if in shadow
            bool inShadow = false;

            if (lights.at(i)->toString() == "DIRECTIONAL_LIGHT") {
                Vec3 lightDirection = static_cast<DirectionalLight*>(lights.at(i))->getLightDirection() * -1;
                shadowRay = lightDirection - intersectionPoint;
                shadowRay.normalize();

                if (scene.getClosestObject(Ray(normalOrigin, shadowRay), lightDist) != nullptr) inShadow = true;

            } else {
                Vec3 lightPos = lights.at(i)->getPos();
                shadowRay = lightPos - intersectionPoint;
                lightDist = shadowRay.calculateMagnitude();
                shadowRay.normalize();
                double s0 = INFINITY;
                if (scene.getClosestObject(Ray(normalOrigin, shadowRay), lightDist) != nullptr &&
                    s0 < lightDist) inShadow = true;
            }

            if (!inShadow) {
                lightIntensity = lightIntensity + normal.dot(shadowRay);
                if (lightIntensity < 0.02) lightIntensity = 0.02;
            }
        }
        lightIntensity = (lightIntensity / lights.size());
        return objectColor * lightIntensity;

    }
    case 1: { //pure specular
        Vec3 reflDirection = ray.d - normal * 2 * (ray.d.dot(normal));
        return objectColor * trace(Ray(normalOrigin, reflDirection), scene, depth);
    }
    case 2: { //glass

    }
    default: {
        return Vec3(0); //object is some other type that isn't compatible with the renderer
    }
    }

    //compute lighting for closestObject
    //check if light
    //calculate intersection spot and normal
}

Material* MRayTracer::getMaterial(std::vector<Material*> materials) {
    for (int i = 0; i < materials.size(); i++) {
        if (materials.at(i)->toString() == "MRAYTRACERMAT") {
            return materials.at(i);
        }
    }
    return nullptr;
}
