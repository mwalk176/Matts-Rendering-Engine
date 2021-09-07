#include "Scene.h"

Scene::Scene() {
	useDefaultScene();
}

Scene::Scene(std::string inputScene, Camera inCam) {
	camera = inCam;
	//camera = Camera(inCam.getColumns(), inCam.getRows());

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

Camera Scene::getCamera() {
	return camera;
}

void Scene::useDefaultScene() {

	//camera = Camera();
	
	//objects = new std::vector<SceneObject*>;
	objects.push_back(new Sphere());
	for (int i = 0; i < objects.size(); i++) {
		//objects.at(i)->toString();
		SceneObject* object = objects.at(i);
		std::cout << object->toString() << std::endl;
	}

	//lights = new std::vector<Light>;

}
