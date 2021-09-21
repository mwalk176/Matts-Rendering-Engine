#include "Scene.h"

Scene::Scene() {
	useDefaultScene();
}

Scene::Scene(std::string inputScene, Camera* inCam) {
	camera = inCam;

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

	backgroundColor = Vec3();

	Vec3 lookFrom = Vec3(0, 0, -4);
	Vec3 lookAt = Vec3(0, 0, 1);
	Vec3 up = Vec3(0, 1, 0);
	double fov = 30.0;

	camera->setCameraCoords(lookFrom, lookAt, up, fov);


	MRayTracerMat* mat = new MRayTracerMat();
	MRayTracerMat* grey = new MRayTracerMat(0.5);
	MRayTracerMat* green = new MRayTracerMat(Vec3(0.2, 1, 0.5));
	MRayTracerMat* azure = new MRayTracerMat(Vec3(0.2, 0.8, 1.0));
	MRayTracerMat* yellow = new MRayTracerMat(Vec3(0.8, 1.0, 0.2));
	MRayTracerMat* refl = new MRayTracerMat(Vec3(1), 1.5, 1);
	MRayTracerMat* glass = new MRayTracerMat(Vec3(1), 1.5, 2);

	MPathTracerMat* pMat = new MPathTracerMat();
	MPathTracerMat* pGrey = new MPathTracerMat(0.5);
	MPathTracerMat* pGreen = new MPathTracerMat(Vec3(0.2, 1, 0.5));
	MPathTracerMat* pAzure = new MPathTracerMat(Vec3(0.2, 0.8, 1.0));
	MPathTracerMat* pYellow = new MPathTracerMat(Vec3(0.8, 1.0, 0.2));
	MPathTracerMat* pRefl = new MPathTracerMat(Vec3(1), Vec3(), 1.5, 1);
	MPathTracerMat* pGlass = new MPathTracerMat(Vec3(1), Vec3(), 1.5, 2);

	MPathTracerMat* light = new MPathTracerMat(Vec3(1), Vec3(1), 1.5, 0);
	MPathTracerMat* dimLight = new MPathTracerMat(Vec3(1), Vec3(0.1), 1.5, 0);

	std::vector<Material*> mats{ mat, pMat };
	std::vector<Material*> greyM{ grey, pGrey };
	std::vector<Material*> greenM{ green, pGreen };
	std::vector<Material*> azureM{ azure, pAzure };
	std::vector<Material*> yellowM{ yellow, pYellow };
	std::vector<Material*> reflM{ refl, pRefl };
	std::vector<Material*> glassM{ glass, pGlass };


	


	objects.push_back(new Sphere(Vec3(0,-1.5,0), 1, azureM));
	objects.push_back(new Sphere(Vec3(3, -1.5, 0), 1, reflM));
	objects.push_back(new Sphere(Vec3(-3, -1.5, 0), 1, glassM));
	//objects.push_back(new Sphere(Vec3(0, -10002.5, 0), 10000, greenM));

	//objects.push_back(new Rectangle(Vec3(1000, -2.5, -1000), Vec3(-1000, -2.5, -1000), Vec3(-1000, -2.5, 1000), Vec3(1000, -2.5, 1000), mats));
	objects.push_back(new Rectangle(Vec3(1000, -2.5, -1000), Vec3(0, -2.5, -1000), Vec3(0, -2.5, 0), Vec3(1000, -2.5, 0), greyM)); //back right
	objects.push_back(new Rectangle(Vec3(0, -2.5, -1000), Vec3(-1000, -2.5, -1000), Vec3(-1000, -2.5, 0), Vec3(0, -2.5, 0), mats)); //back left
	objects.push_back(new Rectangle(Vec3(1000, -2.5, 0), Vec3(0, -2.5, 0), Vec3(0, -2.5, 1000), Vec3(1000, -2.5, 1000), mats)); //front right
	objects.push_back(new Rectangle(Vec3(0, -2.5, 0), Vec3(-1000, -2.5, 0), Vec3(-1000, -2.5, 1000), Vec3(0, -2.5, 1000), greyM)); //front left


	//objects.push_back(new Sphere(Vec3(), 100000, dimLight));
	objects.push_back(new Sphere(Vec3(5, 10, -7), 5, light));
	//objects.push_back(new Rectangle(Vec3(-3.5, 1.5, 5), Vec3(-2.5, 1.5, 5), Vec3(-2.5, 0.5, 5), Vec3(-3.5, 0.5, 5), azureM));
	objects.push_back(new Triangle(Vec3(3.5, 1.5, 5), Vec3(1.5, 1.55, 7), Vec3(0.5, 1.75, 5), azureM));

	lights.push_back(new DirectionalLight(Vec3(1, -1, 0)));
	lights.push_back(new PointLight(Vec3(5, 10, -5)));
	//lights.push_back(new PointLight(Vec3()));

	for (int i = 0; i < objects.size(); i++) {
		//objects.at(i)->toString();
		SceneObject* object = objects.at(i);
		std::cout << object->toString() << std::endl;
	}

	

}
