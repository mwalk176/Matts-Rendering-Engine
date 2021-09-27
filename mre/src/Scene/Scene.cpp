#include "Scene.h"

Scene::Scene() {
	scene1();
}

Scene::Scene(std::string inputScene, Camera* inCam) {
	camera = inCam;

	if (inputScene == "TODO") {
		std::cout << "import scene here" << std::endl;
		scene1(); //TODO: DELETE WHEN IMPLEMENTED
	}
	else {
		scene1();
	}
}

Scene::~Scene() {
	//delete objects;
	//delete lights;

	for (int i = 0; i < objects.size(); i++) {
		delete objects[i];
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

SceneObject* Scene::getClosestObject(Ray r, float& closestPoint) {

	int closestObject = -1;
	float p0 = INFINITY;
	float p1 = INFINITY;

	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->intersect(r, p0, p1)) {
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

bool Scene::inShadow(Ray r, float& lightDist) {
	int closestObject = -1;
	float p0 = INFINITY;
	float p1 = INFINITY;

	for (unsigned int j = 0; j < objects.size(); j++) {
		if (objects.at(j)->intersect(r, p0, p1) &&
			p0 < lightDist) {
			return true;
		}
	}
	return false;
}

void Scene::useDefaultScene() {

	backgroundColor = Vec3();

	Vec3 lookFrom = Vec3(0, 0, -4);
	Vec3 lookAt = Vec3(0, 0, 1);
	Vec3 up = Vec3(0, 1, 0);
	float fov = 30.0;

	camera->setCameraCoords(lookFrom, lookAt, up, fov);


	MRayTracerMat* mat = new MRayTracerMat();
	MRayTracerMat* grey = new MRayTracerMat(0.5f);
	MRayTracerMat* green = new MRayTracerMat(Vec3(0.2f, 1.0f, 0.5f));
	MRayTracerMat* azure = new MRayTracerMat(Vec3(0.2f, 0.8f, 1.0f));
	MRayTracerMat* yellow = new MRayTracerMat(Vec3(0.8f, 1.0f, 0.2f));
	MRayTracerMat* refl = new MRayTracerMat(Vec3(1.0f), 1.5f, 1);
	MRayTracerMat* glass = new MRayTracerMat(Vec3(1.0f), 1.5f, 2);

	MPathTracerMat* pMat = new MPathTracerMat();
	MPathTracerMat* pGrey = new MPathTracerMat(0.5f);
	MPathTracerMat* pGreen = new MPathTracerMat(Vec3(0.2f, 1.0f, 0.5f));
	MPathTracerMat* pAzure = new MPathTracerMat(Vec3(0.2f, 0.8f, 1.0f));
	MPathTracerMat* pYellow = new MPathTracerMat(Vec3(0.8f, 1.0f, 0.2f));
	MPathTracerMat* pRefl = new MPathTracerMat(Vec3(1.0f), Vec3(), 1.5f, 1);
	MPathTracerMat* pGlass = new MPathTracerMat(Vec3(1.0f), Vec3(), 1.5f, 2);

	MPathTracerMat* light = new MPathTracerMat(Vec3(1.0f), Vec3(1.0f), 1.5f, 0);
	MPathTracerMat* dimLight = new MPathTracerMat(Vec3(1.0f), Vec3(0.1f), 1.5f, 0);

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


	objects.push_back(new Sphere(Vec3(), 100000, light));
	objects.push_back(new Sphere(Vec3(5, 10, -7), 5, light));
	//objects.push_back(new Rectangle(Vec3(-3.5, 1.5, 5), Vec3(-2.5, 1.5, 5), Vec3(-2.5, 0.5, 5), Vec3(-3.5, 0.5, 5), azureM));
	objects.push_back(new Triangle(Vec3(3.5, 1.5, 5), Vec3(1.5, 1.55, 7), Vec3(0.5, 1.75, 5), azureM));

	lights.push_back(new DirectionalLight(Vec3(1, -1, 0)));
	lights.push_back(new PointLight(Vec3(5, 10, -5)));
	//lights.push_back(new PointLight(Vec3()));

	for (int i = 0; i < objects.size(); i++) {
		//objects[i]->toString();
		SceneObject* object = objects[i];
		std::cout << object->toString() << std::endl;
	}

	

}

void Scene::scene1() {
	backgroundColor = Vec3();

	Vec3 lookFrom = Vec3(0, 0, -5);
	Vec3 lookAt = Vec3(0, 0, 1);
	Vec3 up = Vec3(0, 1, 0);
	float fov = 10.0;

	camera->setCameraCoords(lookFrom, lookAt, up, fov);


	MPathTracerMat* pMat = new MPathTracerMat();
	MPathTracerMat* pGrey = new MPathTracerMat(0.9);
	MPathTracerMat* pGreen = new MPathTracerMat(Vec3(0.2, 1, 0.5));
	MPathTracerMat* pAzure = new MPathTracerMat(Vec3(0.2, 0.8, 1.0));
	MPathTracerMat* pYellow = new MPathTracerMat(Vec3(0.8, 1.0, 0.2));
	MPathTracerMat* pRefl = new MPathTracerMat(Vec3(1), Vec3(), 1.5, 1);
	MPathTracerMat* pGlass = new MPathTracerMat(Vec3(1), Vec3(), 1.5, 2);

	MPathTracerMat* light = new MPathTracerMat(Vec3(1), Vec3(3), 1.5, 0);
	MPathTracerMat* light2 = new MPathTracerMat(Vec3(1), Vec3(1), 1.5, 0);
	MPathTracerMat* light3 = new MPathTracerMat(Vec3(1), Vec3(0.9), 1.5, 0);
	MPathTracerMat* dimLight = new MPathTracerMat(Vec3(1), Vec3(0.5), 1.5, 0);


	objects.push_back(new Rectangle(
		Vec3(0.0, -0.820135, -0.278169), 
		Vec3(0.0, -0.0111184, -0.865954), 
		Vec3(0.707107, 0.404509, -0.293893), 
		Vec3(0.707107, -0.404509, 0.293893), pAzure));
	objects.push_back(new Rectangle(
		Vec3(0.0, -0.820135, -0.278169), 
		Vec3(-0.707107, -0.404509, 0.293893), 
		Vec3(-0.707107, 0.404509, -0.293893), 
		Vec3(0.0, -0.0111184, -0.865954),
		pAzure));
	objects.push_back(new Rectangle(
		Vec3(0.0, -0.0111184, -0.865954), 
		Vec3(-0.707107, 0.404509, -0.293893), 
		Vec3(0.0, 0.820135, 0.278169), 
		Vec3(0.707107, 0.404509, -0.293893),
		pAzure));

	objects.push_back(new Sphere(Vec3(0), 10000, dimLight));
	objects.push_back(new Sphere(Vec3(2, -0.95, 0), 0.5, light));
	objects.push_back(new Sphere(Vec3(-2, -0.95, 0), 0.5, light));
	objects.push_back(new Sphere(Vec3(0, -1.05, -1), 0.4, pGlass));
	objects.push_back(new Sphere(Vec3(-1, -1.15, 1), 0.3, pRefl));
	objects.push_back(new Sphere(Vec3(1, -1.15, 1), 0.3, pRefl));
	objects.push_back(new Triangle(Vec3(0, 2, 5), Vec3(-1, 3, 5), Vec3(1, 3, 5), light2));

	objects.push_back(new Sphere(Vec3(0, -10001.5, 0), 10000, pGrey));

}
