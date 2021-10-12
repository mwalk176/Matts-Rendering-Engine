#include "MPathTracer.h"

MPathTracer::MPathTracer() {
	backgroundColor = scene->getBackgroundColor();
}

MPathTracer::MPathTracer(Scene* s) {
	scene = s;
	objects = s->getObjects();
	lights = s->getLights();
}

Vec3 MPathTracer::render(Ray camRay) {
    Vec3 col = trace(camRay, 0, true);
    return col;
}

Vec3 MPathTracer::trace(Ray ray, int depth, bool calculateEmission) {
	if (depth > 6) return Vec3();
	depth += 1;


	

	float closestPoint = INFINITY;

	//check for intersection with object
	SceneObject* closestObject = scene->getClosestObject(ray, closestPoint);

	if (closestObject == nullptr) { //nothing was hit
		//only return the background if it's from a primary ray
		if (depth == 1) return backgroundColor;

		//return black otherwise so it doesn't affect object illumination
		return Vec3(); //BUT MAYBE WE WANT IT TO AFFECT ILLUMINATION???? 
	}

	MPathTracerMat* mat = static_cast<MPathTracerMat*>(closestObject->getMaterial(2));

	if (mat == nullptr) return Vec3();

	//it's a light so just return the light color
	if (mat->emissionColor.calculateMagnitude() != 0) {
		return Vec3(mat->emissionColor.x, mat->emissionColor.y, mat->emissionColor.z) * mat->gamma;
	}

	Vec3 color = mat->color;

	float brightestColor = mat->color.x;
	if (mat->color.y > brightestColor) brightestColor = mat->color.y;
	if (mat->color.z > brightestColor) brightestColor = mat->color.z;
	if (depth > 5) {
		if ((float)rand() / RAND_MAX < brightestColor) {
			color = mat->color * (1 / brightestColor);
		}
		else {
			return mat->emissionColor;
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

	float epsilon = 8e-5f;
	if (closestObject->shapeType == SPHERE) {
		Sphere* sphereLight = static_cast<Sphere*>(closestObject);
		epsilon = 8e-6f * (sphereLight->getRadius() + 1.0f);
	}
	Vec3 normalOrigin = intersectionPoint + normal * epsilon;


	switch (mat->type) {
	case 0: {//diffuse

		Vec3 randomReflection = computeRandomReflection(alignedNormal);
		

		Vec3 lightValue = computeShadowRay(normalOrigin, intersectionPoint,
			alignedNormal, mat->color, normal);

		if (calculateEmission) {
			color = mat->emissionColor + lightValue +
				mat->color * trace(Ray(normalOrigin,
					randomReflection), depth, false);
		}
		else {
			color = lightValue + mat->color *
				trace(Ray(normalOrigin, randomReflection), depth, true); //maybe keep it at false?
		}

		/*if (depth == 1) end = std::chrono::system_clock::now();
		if (depth == 1) elapsed_seconds = end - start;
		if (depth == 1) std::cout << "Recursive Path Trace elapsed time: " << elapsed_seconds.count() << "s\n\n\n";*/

		return color;
	}
	case 1: {//mirror
		if (mat->roughness == 0) {
			Vec3 reflDirection = ray.d - normal * 2 * (ray.d.dot(normal));
			return mat->emissionColor + mat->color * trace(Ray(normalOrigin, reflDirection), depth, true);
		}

		Vec3 reflDirection = ray.d - normal * 2 * (ray.d.dot(normal));
		Vec3 newReflRay = jitterRay(alignedNormal, reflDirection, mat->roughness);

		return mat->emissionColor + mat->color * trace(Ray(normalOrigin, newReflRay), depth, true);

	}
	case 2: {//glass
		//first calculate reflection
		Vec3 reflDirection = ray.d - normal * 2 * (ray.d.dot(normal));
		if (mat->roughness > 0) {
			Vec3 newReflRay = jitterRay(normal, reflDirection, mat->roughness);
			reflDirection = newReflRay;
		}

		epsilon = 1e-3;

		float iorValue = mat->IOR;
		bool outGoingIn = false;
		if (normal.dot(alignedNormal) > 0) outGoingIn = true;
		if (outGoingIn) iorValue = 1 / iorValue;
		float normDirAngle = ray.d.dot(alignedNormal);

		//then check for total internal reflection
		float interiorAngle = 1 - (iorValue * iorValue) * (1 - normDirAngle * normDirAngle);
		if (interiorAngle < 0) {
			return mat->emissionColor + mat->color * trace(Ray(normalOrigin, reflDirection), depth, true);

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
		}
		else {
			transmissionRay = ray.d * iorValue - normal * (-1 * (normDirAngle * iorValue + sqrt(interiorAngle)));
			transmissionRay.normalize();

			refractOrigin = intersectionPoint + normal * epsilon;

			theta = transmissionRay.dot(normal);
		}
		if (mat->roughness > 0) {
			Vec3 newTransmissionRay = jitterRay(normal, transmissionRay, mat->roughness);
			transmissionRay = newTransmissionRay;
		}

		//calculate incidence of relfection (f0) and the fresnel equation
		float f0 = ((iorValue - 1) * (iorValue - 1)) / ((iorValue + 1) * (iorValue + 1));
		float fresnel = f0 + (1 - f0) * ((1 - theta) * (1 - theta) * (1 - theta) * (1 - theta) * (1 - theta));


		//based off a random threshold, after 2 bounces do either a refract or a reflect trace
		if (depth > 2) {
			float fresnelThreshold = fresnel * 0.5 + 0.25;
			if (((float)rand() / RAND_MAX) < fresnelThreshold) {
				Vec3 col = mat->emissionColor + mat->color * trace(Ray(normalOrigin, reflDirection), depth, true) * (fresnel / fresnelThreshold) * mat->gamma;
				return col;

			}
			else {
				Vec3 col = mat->emissionColor + mat->color * trace(Ray(refractOrigin, transmissionRay), depth, true) * ((1 - fresnel) / (1 - fresnelThreshold)) * mat->gamma;
				return col;
			}
		}
		else {
			Vec3 refl = trace(Ray(normalOrigin, reflDirection), depth, true) * fresnel;
			Vec3 refr = trace(Ray(refractOrigin, transmissionRay), depth, true) * (1 - fresnel);
			Vec3 col = mat->emissionColor + mat->color * (refl + refr) * mat->gamma;
			return col;
		}
	}
	default: { //the sphere is something else and we don't know what it is
		return Vec3(0);
	}
	}
}

Vec3 MPathTracer::computeRandomReflection(Vec3 alignedNormal) {
	float randomAngle = M_PI * 2 * ((float)rand() / RAND_MAX);
	float distanceModifier = (float)rand() / RAND_MAX;
	float distanceModifier2 = sqrt(distanceModifier);

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

	return randomReflection;
}

Vec3 MPathTracer::computeShadowRay(Vec3 normalOrigin, Vec3 intersectionPoint, 
	Vec3 alignedNormal, Vec3 objectColor, Vec3 normal) {

	Vec3 lightValue = Vec3();

	//Shadow Ray computation for physical lights  
	for (unsigned int i = 0; i < objects.size(); i++) {
		SceneObject* sObject = objects[i];
		MPathTracerMat* sMat = static_cast<MPathTracerMat*>(sObject->getMaterial(2));
		if (sMat == nullptr) continue;
		if (sMat->emissionColor.calculateMagnitude() <= 0) continue; //we only want lights

		//shoot another ray towards the face of the light
		Vec3 shadowRay = sObject->getPos() - intersectionPoint;
		Vec3 normalFromLight = intersectionPoint - sObject->getPos();
		float lightDist = shadowRay.calculateMagnitude();
		shadowRay.normalize();

		bool insideLight = false;
		if (sObject->shapeType == SPHERE) {
			Sphere* sphereLight = static_cast<Sphere*>(sObject);
			if (lightDist < sphereLight->getRadius()) {
				//we're inside the light
				continue;
			}
		}

		float angleToObject = 0;
		Vec3 newShadowRay = sObject->
			getNewDirectionTowardsLight(shadowRay, alignedNormal,
				normalFromLight, angleToObject, intersectionPoint);

		if (!scene->inShadow(Ray(normalOrigin, newShadowRay), lightDist)) {
			float brdf = 2 * M_PI * (1.0 - angleToObject);
			lightValue = lightValue + objectColor *
				(alignedNormal.dot(newShadowRay) * brdf) * M_1_PI;
		}

	}

	//std::vector<Light*> lights = scene->getLights();

	//Shadow Ray calculation for point and directional lights
	for (unsigned int i = 0; i < lights.size(); i++) {

		float lightDist = INFINITY;
		Vec3 shadowRay;

		//check if in shadow
		bool inShadow = false;
		float s0 = INFINITY;

		if (lights[i]->lightType == DIRECTIONAL_LIGHT) {
			Vec3 lightDirection = static_cast<DirectionalLight*>(lights[i])->getLightDirection() * -1;
			shadowRay = lightDirection;// -intersectionPoint;
			shadowRay.normalize();

			if (scene->getClosestObject(Ray(normalOrigin, shadowRay), s0) != nullptr) inShadow = true;

		}
		else {
			Vec3 lightPos = lights[i]->getPos();
			shadowRay = lightPos - intersectionPoint;
			lightDist = shadowRay.calculateMagnitude();
			shadowRay.normalize();
			SceneObject* closestShadowObj = scene->getClosestObject(Ray(normalOrigin, shadowRay), s0);
			if (closestShadowObj != nullptr && s0 < lightDist) inShadow = true;
		}

		if (!inShadow) {
			lightValue = lightValue + normal.dot(shadowRay);
			if (lightValue.calculateMagnitude() < 0.02) lightValue = Vec3(0.02f);
		}
	
	}

	return lightValue;
}

Vec3 MPathTracer::jitterRay(Vec3 n, Vec3 d, float roughness) {

	//build a coordinate space in the hemisphere of the reflection ray
	Vec3 se1 = Vec3(0);
	if (fabs(n.x) > fabs(n.y)) {
		se1 = Vec3(d.z, 0, -d.x) / sqrt(d.x * d.x + d.z * d.z);
	} else {
		se1 = Vec3(0, -d.z, d.y) / sqrt(d.y * d.y + d.z * d.z);
	}
	se1.normalize();
	Vec3 se2 = d.cross(se1);
	se2.normalize();

	//calculate a new random reflection in a radius around the original ray
	float angleToSphere = sqrt(1 - roughness / n.dot(n));
	float randX = (float)rand() / RAND_MAX; //get us a random point
	float randomAngle2 = M_PI * 2 * ((float)rand() / RAND_MAX);
	float angleCos = 1 - randX + randX * angleToSphere;
	float angleSin = sqrt(1 - angleCos * angleCos);
	Vec3 newReflRay = se1 * cos(randomAngle2) * angleSin + se2 * sin(randomAngle2) * angleSin + d * angleCos;
	newReflRay.normalize();

	return newReflRay;

}
