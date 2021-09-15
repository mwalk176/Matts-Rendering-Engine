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

Vec3 Scene::getBackgroundColor() {
	return backgroundColor;
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

	backgroundColor = Vec3(0.2);


	MRayTracerMat* mat = new MRayTracerMat();
	MRayTracerMat* green = new MRayTracerMat(Vec3(0.2, 1, 0.5));
	MRayTracerMat* azure = new MRayTracerMat(Vec3(0.2, 0.8, 1.0));
	MRayTracerMat* yellow = new MRayTracerMat(Vec3(0.8, 1.0, 0.2));
	MRayTracerMat* refl = new MRayTracerMat(Vec3(1), 1.5, 1);
	MRayTracerMat* glass = new MRayTracerMat(Vec3(1), 1.5, 2);


	objects.push_back(new Sphere(Vec3(0,-1.5,5), 1, azure));
	objects.push_back(new Sphere(Vec3(3, -1.5, 5), 1, refl));
	objects.push_back(new Sphere(Vec3(-3, -1.5, 5), 1, glass));
	objects.push_back(new Sphere(Vec3(0, -10002.5, 0), 10000, green));

	objects.push_back(new Rectangle(Vec3(-3.5, 1.5, 5), Vec3(-2.5, 1.5, 5), Vec3(-2.5, 0.5, 5), Vec3(-3.5, 0.5, 5), azure));
	objects.push_back(new Triangle(Vec3(2.5, 1.5, 5), Vec3(3.5, 1.5, 5), Vec3(3, 0.5, 5), yellow));

	lights.push_back(new DirectionalLight(Vec3(1, -1, 0)));
	lights.push_back(new PointLight(Vec3(5, 10, 0)));
	//lights.push_back(new PointLight(Vec3()));

	for (int i = 0; i < objects.size(); i++) {
		//objects.at(i)->toString();
		SceneObject* object = objects.at(i);
		std::cout << object->toString() << std::endl;
	}

	

}
