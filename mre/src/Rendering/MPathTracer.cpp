#include "MPathTracer.h"

Vec3 MPathTracer::render(Ray camRay, Scene& scene) {
    Vec3 col = trace(camRay, scene, 0, true);
    return col;
}

Vec3 MPathTracer::trace(Ray ray, Scene& scene, int depth, bool calculateEmission) {
	if (depth > 6) return Vec3();
	depth += 1;

	Vec3 backgroundColor = scene.getBackgroundColor();


	double closestPoint = INFINITY;

	//check for intersection with object
	//int closestObject = scene.getClosestObject(rayOrigin, rayDirection, scene, closestPoint);

	SceneObject* closestObject = scene.getClosestObject(ray, closestPoint);

	if (closestObject == nullptr) { //nothing was hit
		//only return the background if it's from a primary ray
		if (depth == 1) return backgroundColor;

		//return black otherwise so it doesn't affect object illumination
		return Vec3();
	}

	MPathTracerMat* mat = static_cast<MPathTracerMat*>(closestObject->getMaterial("MPATHTRACERMAT"));
	//MPathTracerMat* mat = new MPathTracerMat();
	if (mat == nullptr) return Vec3();

	Vec3 objectColor = mat->getColor();
	Vec3 emissionColor = mat->getEmission();

	//it's a light so just return the light color
	if (emissionColor.calculateMagnitude() != 0) {
		return Vec3(emissionColor.x, emissionColor.y, emissionColor.z) * mat->getGamma();
	}

	double brightestColor = objectColor.x;
	if (objectColor.y > brightestColor) brightestColor = objectColor.y;
	if (objectColor.z > brightestColor) brightestColor = objectColor.z;
	if (depth > 5) {
		if ((double)rand() / RAND_MAX < brightestColor) {
			objectColor = objectColor * (1 / brightestColor);
		}
		else {
			return emissionColor;
		}
	}

	//calculate spot where it intersected and the normal
	Vec3 intersectionPoint = ray.o + ray.d * closestPoint;
	Vec3 normal = closestObject->computeNormal(intersectionPoint);
	normal.normalize();
	Vec3 alignedNormal = normal; //normal that is pointing out of the sphere
	bool outsideSphere = true;
	if (normal.dot(ray.d) >= 0) {
		outsideSphere = false;
		alignedNormal = normal * -1;
	}

	double epsilon = 8e-5;
	if (closestObject->toString() == "SPHERE") {
		Sphere* sphereLight = static_cast<Sphere*>(closestObject);
		epsilon = 8e-6 * (sphereLight->getRadius() + 1.0);
	}
	Vec3 normalOrigin = intersectionPoint + normal * epsilon;

	Vec3 lightValue = Vec3(0);

	switch (mat->getType()) {
	case 0: {//diffuse

		//diffuse reflections
		//calculate a random ray direction in the hemisphere around the normal
		double randomAngle = M_PI * 2 * ((double)rand() / RAND_MAX);
		double distanceModifier = (double)rand() / RAND_MAX;
		double distanceModifier2 = sqrt(distanceModifier);

		//get a set of basis vectors to have a hemisphere around object's normal
		Vec3 e1 = Vec3(0);

		//make sure the alignedNormal is the "up" vector in the hemisphere
		if (fabs(alignedNormal.x) > fabs(alignedNormal.y)) {
			e1 = Vec3(alignedNormal.z, 0, -alignedNormal.x) /
				sqrt(alignedNormal.x * alignedNormal.x +
					alignedNormal.z * alignedNormal.z);
		}
		else {
			e1 = Vec3(0, -alignedNormal.z, alignedNormal.y) /
				sqrt(alignedNormal.y * alignedNormal.y +
					alignedNormal.z * alignedNormal.z);
		}
		e1.normalize();
		Vec3 e2 = alignedNormal.cross(e1);
		e2.normalize();

		Vec3 randomReflection = (e1 * cos(randomAngle) * distanceModifier2 +
			e2 * sin(randomAngle) * distanceModifier2 +
			alignedNormal * sqrt(1 - distanceModifier));
		randomReflection.normalize();

		//Shadow Ray computation for physical lights 
		for (unsigned int i = 0; i < scene.getObjects().size(); i++) {
			SceneObject* sObject = scene.getObjects().at(i);
			MPathTracerMat* sMat = static_cast<MPathTracerMat*>(sObject->getMaterial("MPATHTRACERMAT"));
			if (sMat == nullptr) continue;
			if (sMat->getEmission().calculateMagnitude() <= 0) continue; //we only want lights

			//shoot another ray towards the face of the light
			Vec3 shadowRay = sObject->getPos() - intersectionPoint;
			Vec3 normalFromLight = intersectionPoint - sObject->getPos();
			double lightDist = shadowRay.calculateMagnitude();
			shadowRay.normalize();

			bool insideLight = false;
			if (sObject->toString() == "SPHERE") {
				Sphere* sphereLight = static_cast<Sphere*>(sObject);
				if (lightDist < sphereLight->getRadius()) {
					//we're inside the light
					continue;
				}
			}


			double angleToObject = 0;
			Vec3 newShadowRay = sObject->
				getNewDirectionTowardsLight(shadowRay, alignedNormal,
					normalFromLight, angleToObject, intersectionPoint);

			double s0 = 0;
			double s1 = 0;
			bool inShadow = false;


			//check to see if another object is inbetween the light
			for (unsigned int j = 0; j < scene.getObjects().size(); j++) {
				if (scene.getObjects().at(j)->intersect(Ray(
					normalOrigin, newShadowRay), s0, s1) &&
					s0 < lightDist) {
					inShadow = true;
					break;
				}
			}
			if (!inShadow) {
				double brdf = 2 * M_PI * (1.0 - angleToObject);
				lightValue = lightValue + objectColor *
					(alignedNormal.dot(newShadowRay) * brdf) * M_1_PI;
			}

		}

		std::vector<Light*> lights = scene.getLights();

		//Shadow Ray calculation for point and directional lights
		for (unsigned int i = 0; i < lights.size(); i++) {

			double lightDist = INFINITY;
			Vec3 shadowRay;

			//check if in shadow
			bool inShadow = false;
			double s0 = INFINITY;

			if (lights.at(i)->toString() == "DIRECTIONAL_LIGHT") {
				Vec3 lightDirection = static_cast<DirectionalLight*>(lights.at(i))->getLightDirection() * -1;
				shadowRay = lightDirection;// -intersectionPoint;
				shadowRay.normalize();

				if (scene.getClosestObject(Ray(normalOrigin, shadowRay), s0) != nullptr) inShadow = true;

			}
			else {
				Vec3 lightPos = lights.at(i)->getPos();
				shadowRay = lightPos - intersectionPoint;
				lightDist = shadowRay.calculateMagnitude();
				shadowRay.normalize();
				SceneObject* closestShadowObj = scene.getClosestObject(Ray(normalOrigin, shadowRay), s0);
				if (closestShadowObj != nullptr && s0 < lightDist) inShadow = true;
			}

			if (!inShadow) {
				lightValue = lightValue + normal.dot(shadowRay);
				if (lightValue.calculateMagnitude() < 0.02) lightValue = Vec3(0.02);
			}
		}
		if (calculateEmission) {
			objectColor = emissionColor + lightValue +
				objectColor * trace(Ray(normalOrigin,
					randomReflection), scene, depth, false);
		}
		else {
			objectColor = lightValue + objectColor *
				trace(Ray(normalOrigin, randomReflection),
					scene, depth, true);
		}

		return objectColor;
	}
	case 1: {//mirror
		Vec3 reflDirection = ray.d - normal * 2 * (ray.d.dot(normal));
		return emissionColor + objectColor * trace(Ray(normalOrigin, reflDirection), scene, depth, true);
	}
	case 2: {//glass
		//first calculate reflection
		Vec3 reflDirection = ray.d - normal * 2 * (ray.d.dot(normal));

		epsilon = 1e-3;

		double iorValue = mat->getIOR();
		bool outGoingIn = false;
		if (normal.dot(alignedNormal) > 0) outGoingIn = true;
		if (outGoingIn) iorValue = 1 / iorValue;
		double normDirAngle = ray.d.dot(alignedNormal);

		//then check for total internal reflection
		double interiorAngle = 1 - (iorValue * iorValue) * (1 - normDirAngle * normDirAngle);
		if (interiorAngle < 0) {
			return emissionColor + objectColor * trace(Ray(normalOrigin, reflDirection), scene, depth, true);

		}

		//then calculate refraction
		Vec3 transmissionRay = Vec3(0);
		Vec3 refractOrigin = intersectionPoint - normal * epsilon;
		double theta = 0;

		if (outGoingIn) {
			transmissionRay = ray.d * iorValue - normal * (normDirAngle * iorValue + sqrt(interiorAngle));
			transmissionRay.normalize();

			refractOrigin = intersectionPoint - normal * epsilon;

			theta = -normDirAngle;
		}
		else {
			transmissionRay = ray.d * iorValue - normal * (-1 * (normDirAngle * iorValue + sqrt(interiorAngle)));
			transmissionRay.normalize();

			refractOrigin = intersectionPoint + normal * epsilon;

			theta = transmissionRay.dot(normal);
		}

		//calculate incidence of relfection (f0) and the fresnel equation
		double f0 = ((iorValue - 1) * (iorValue - 1)) / ((iorValue + 1) * (iorValue + 1));
		//double f0 = ((scene[closestObject]->IOR - 1) * (scene[closestObject]->IOR - 1)) / ((scene[closestObject]->IOR + 1) * (scene[closestObject]->IOR + 1));
		double fresnel = f0 + (1 - f0) * ((1 - theta) * (1 - theta) * (1 - theta) * (1 - theta) * (1 - theta));


		//check if angle of incidence is too shallow,
		if (depth > 2) {
			double fresnelThreshold = fresnel * 0.5 + 0.25;
			if (((double)rand() / RAND_MAX) < fresnelThreshold) {
				Vec3 col = emissionColor + objectColor * trace(Ray(normalOrigin, reflDirection), scene, depth, true) * (fresnel / fresnelThreshold) * mat->getGamma();
				return col;

			}
			else {
				Vec3 col = emissionColor + objectColor * trace(Ray(refractOrigin, transmissionRay), scene, depth, true) * ((1 - fresnel) / (1 - fresnelThreshold)) * mat->getGamma();
				return col;
			}
		}
		else {
			Vec3 refl = trace(Ray(normalOrigin, reflDirection), scene, depth, true) * fresnel;
			Vec3 refr = trace(Ray(refractOrigin, transmissionRay), scene, depth, true) * (1 - fresnel);
			Vec3 col = emissionColor + objectColor * (refl + refr) * mat->getGamma();
			return col;
		}
	}
	case 3: {//glossy

		double roughness = 0.1; //0 is mirror, 1 is completely rough

		Vec3 reflDirection = ray.d - normal * 2 * (ray.d.dot(normal));

		//build a coordinate space in the hemisphere of the shadowray light
		Vec3 se1 = Vec3(0);
		if (fabs(alignedNormal.x) > fabs(alignedNormal.y)) {
			se1 = Vec3(reflDirection.z, 0, -reflDirection.x) / sqrt(reflDirection.x * reflDirection.x + reflDirection.z * reflDirection.z);
		}
		else {
			se1 = Vec3(0, -reflDirection.z, reflDirection.y) / sqrt(reflDirection.y * reflDirection.y + reflDirection.z * reflDirection.z);
		}
		se1.normalize();
		Vec3 se2 = reflDirection.cross(se1);
		se2.normalize();

		//calculate a random direction towards light
		double angleToSphere = sqrt(1 - roughness / normal.dot(normal));
		double randX = (double)rand() / RAND_MAX; //get us a random point
		double randomAngle2 = M_PI * 2 * ((double)rand() / RAND_MAX);
		double angleCos = 1 - randX + randX * angleToSphere;
		double angleSin = sqrt(1 - angleCos * angleCos);
		Vec3 newReflRay = se1 * cos(randomAngle2) * angleSin + se2 * sin(randomAngle2) * angleSin + reflDirection * angleCos;
		newReflRay.normalize();

		return emissionColor + objectColor * trace(Ray(normalOrigin, newReflRay), scene, depth, true);

	}
	default: { //the sphere is something else and we don't know what it is
		return Vec3(0);
	}
	}
}
