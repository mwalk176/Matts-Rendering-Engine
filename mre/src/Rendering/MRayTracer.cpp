#include "MRayTracer.h"

Vec3 MRayTracer::render(Ray camRay, Scene& scene) {

    Vec3 col = trace(camRay, scene, 0);
    return col;



    
}

Vec3 MRayTracer::trace(Ray ray, Scene& scene, int depth) {

    if (depth > 6) return Vec3();
    depth++; //increment depth


    float epsilon = 8e-5;

    //first find closest object (if there is one)
    float closestPoint = INFINITY;
    SceneObject* closestObject = scene.getClosestObject(ray, closestPoint);

    if (closestObject == nullptr) return scene.getBackgroundColor(); //nothing was hit

    
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
    MRayTracerMat* mat = static_cast<MRayTracerMat*>(closestObject->getMaterial("MRAYTRACERMAT"));
    if (mat == nullptr) return Vec3(); //no compatible material found
    Vec3 objectColor = mat->getColor();
    
    switch (mat->getType()) {
    case 0: { //difuse

        std::vector<Light*> lights = scene.getLights();

        float lightIntensity = 0;

        for (unsigned int i = 0; i < lights.size(); i++) {
            
            float lightDist = INFINITY;
            Vec3 shadowRay;

            //check if in shadow
            bool inShadow = false;
            float s0 = INFINITY;

            if (lights.at(i)->toString() == "DIRECTIONAL_LIGHT") {
                Vec3 lightDirection = static_cast<DirectionalLight*>(lights.at(i))->getLightDirection() * -1;
                shadowRay = lightDirection;// -intersectionPoint;
                shadowRay.normalize();

                if (scene.getClosestObject(Ray(normalOrigin, shadowRay), s0) != nullptr) inShadow = true;

            } else {
                Vec3 lightPos = lights.at(i)->getPos();
                shadowRay = lightPos - intersectionPoint;
                lightDist = shadowRay.calculateMagnitude();
                shadowRay.normalize();
                SceneObject* closestShadowObj = scene.getClosestObject(Ray(normalOrigin, shadowRay), s0);
                if (closestShadowObj != nullptr && s0 < lightDist) inShadow = true;
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
        //first calculate reflection
        Vec3 reflDirection = ray.d - normal * 2 * (ray.d.dot(normal));

        epsilon = 1e-3;

        float iorValue = mat->getIOR();
        bool outGoingIn = false;
        if (normal.dot(alignedNormal) > 0) outGoingIn = true;
        if (outGoingIn) iorValue = 1 / iorValue;
        float normDirAngle = ray.d.dot(alignedNormal);

        //then check for total internal reflection
        float interiorAngle = 1 - (iorValue * iorValue) * (1 - normDirAngle * normDirAngle);
        if (interiorAngle < 0) {
            return objectColor * trace(Ray(normalOrigin, reflDirection), scene, depth);

        }

        //then calculate refraction
        Vec3 transmissionRay = Vec3(0);
        Vec3 refractOrigin = intersectionPoint - normal * epsilon;
        float theta = 0;

        if (outGoingIn) {
            transmissionRay = ray.d * iorValue - normal * (normDirAngle * iorValue + sqrt(interiorAngle));
            transmissionRay.normalize();

            refractOrigin = intersectionPoint - normal * epsilon;

            theta = -normDirAngle;
        } else {
            transmissionRay = ray.d * iorValue - normal * (-1 * (normDirAngle * iorValue + sqrt(interiorAngle)));
            transmissionRay.normalize();

            refractOrigin = intersectionPoint + normal * epsilon;

            theta = transmissionRay.dot(normal);
        }

        //calculate incidence of relfection (f0) and the fresnel equation
        float IOR = mat->getIOR();
        float f0 = ((IOR - 1) * (IOR - 1)) / ((IOR + 1) * (IOR + 1));
        float fresnel = f0 + (1 - f0) * ((1 - theta) * (1 - theta) * (1 - theta) * (1 - theta) * (1 - theta));

        float gammaBoost = 1.0;
        //check if angle of incidence is too shallow,
        if (depth > 2) {
            float fresnelThreshold = fresnel * 0.5 + 0.25;
            if (((float)rand() / RAND_MAX) < fresnelThreshold) {
                Vec3 col = objectColor * trace(Ray(normalOrigin, reflDirection), scene, depth) * (fresnel / fresnelThreshold) * gammaBoost;
                return col;

            } else {
                Vec3 col = objectColor * trace(Ray(refractOrigin, transmissionRay), scene, depth) * ((1 - fresnel) / (1 - fresnelThreshold)) * gammaBoost;
                return col;
            }
        } else {
            Vec3 refl = trace(Ray(normalOrigin, reflDirection), scene, depth) * fresnel;
            Vec3 refr = trace(Ray(refractOrigin, transmissionRay), scene, depth) * (1 - fresnel);
            Vec3 col = objectColor * (refl + refr) * gammaBoost;
            return col;
        }
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
