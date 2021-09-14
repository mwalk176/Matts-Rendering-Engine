#include "Scene.h"

Scene::Scene() {
	useDefaultScene();
}

Scene::Scene(std::string inputScene, Camera* inCam) {
	//Camera cam();
	//camera = cam;
	camera = inCam;
	//camera = Camera();

	if (inputScene == "TODO") {
		std::cout << "import scene here" << std::endl;
		useDefaultScene(); //TODO: DELETE WHEN IMPLEMENTED
	}
	else {
		useDefaultScene();
	}
}

Scene::~Scene() {
	//delete objects;
	//delete lights;

	for (int i = 0; i < objects.size(); i++) {
		delete objects.at(i);
	}
}

Camera* Scene::getCamera() {
	return camera;
}

std::vector<SceneObject*> Scene::getObjects() {
	return objects;
}

std::vector<Light*> Scene::getLights() {
	return lights;
}

SceneObject* Scene::getClosestObject(Ray r, double& closestPoint) {

	int closestObject = -1;
	double p0 = INFINITY;
	double p1 = INFINITY;

	for (int i = 0; i < objects.size(); i++) {
		if (objects.at(i)->intersect(r, p0, p1)) {
			if (p0 < closestPoint) {
				closestPoint = p0;
				closestObject = i;
			} else {
				continue;
			}

		}
	}

	if (closestObject != -1) return objects.at(closestObject);
	else return nullptr;
}

void Scene::useDefaultScene() {


	MRayTracerMat* mat = new MRayTracerMat();
	MRayTracerMat* refl = new MRayTracerMat(Vec3(1), 1.5, 1);


	objects.push_back(new Sphere(Vec3(0,0,5), 1, mat));
	objects.push_back(new Sphere(Vec3(3, 0, 5), 1, refl));
	objects.push_back(new Sphere(Vec3(0, -10004, 0), 10000, mat));

	lights.push_back(new DirectionalLight(Vec3(5, -1, 5)));

	for (int i = 0; i < objects.size(); i++) {
		//objects.at(i)->toString();
		SceneObject* object = objects.at(i);
		std::cout << object->toString() << std::endl;
	}

	

}
