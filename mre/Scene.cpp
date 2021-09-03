#include "Scene.h"

Scene::Scene() {
	useDefaultScene();
}

Scene::Scene(std::string inputScene) {
	if (inputScene == "TODO") {
		std::cout << "import scene here" << std::endl;
		useDefaultScene(); //TODO: DELETE WHEN IMPLEMENTED
	}
	else {
		useDefaultScene();
	}
}

Scene::~Scene() {
	delete objects;
	delete lights;

	/*for (int i = 0; i < objects->size(); i++) {
		delete objects->at(i);
	}*/
}

void Scene::useDefaultScene() {

	camera = Camera();
	objects = new std::vector<SceneObject>;
	lights = new std::vector<Light>;

}
